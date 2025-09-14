/**
 * Game.cpp
 *
 * Funkcionalnost:
 * - Implementacija glavne logike igre: upravljanje robotom, minotaurom i predmetima
 * - Sadrzi funkcionalnosti za kretanje, prikaz lavirinta i obradu kraja igre
 *
 * Autori: Ognjen 
 * Datum poslednje izmjene: 14.9.2025.
 */

#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Game.h"
#include "FogItem.h"
#include "SwordItem.h"
#include "ShieldItem.h"
#include "HammerItem.h"
#include "ReportGenerator.h"

using namespace std;


/**
 * Konstruktor klase Game
 *
 * Funkcionalnost:
 * - Inicijalizuje lavirint sa prosledjenim brojem redova, kolona i brojem predmeta
 * - Postavlja osnovne parametre igre
 *
 * @param pRows broj redova lavirinta
 * @param pColumns broj kolona lavirinta
 * @param pItemNumber ukupni broj predmeta koji se nasumicno rasporedjuju po lavirintu
 */
Game::Game(int pRows, int pColumns, int pItemNumber)

	: itemNumber(pItemNumber),
	maze(pColumns, pRows, pItemNumber),
	gameOver(false),
	isWon(false),
	items(), 
	isMinotaurAlive(true){ }
	
/**
 * Destruktor klase Game
 *
 * Funkcionalnost:
 * - Oslobadja dinamicki alociranu memoriju za sve aktivne predmete
 */
Game::~Game(){
	for (Item* item : items) {
		delete item;
	}
}

/**
 * Osvjezava stanje igre
 *
 * Funkcionalnost:
 * - Resetuje sve efekte (magla, mac, stit, cekic)
 * - Smanjuje trajanje aktivnih predmeta
 * - Brise predmete kojima je istekao efekat
 * - Prikazuje trenutno stanje igre
 */
void Game::refresh(){
	system("CLS");

	isFogActive = false;
	isSwordActive = false;
	isShieldActive = false;
	isHammerActive = false;

	for (Item* item : items) {
		item->decreaseDuration();
		if (item->getDuration() == -1) {
			items.erase(remove(items.begin(), items.end(), item), items.end());
			delete item;
			continue;
		}
		switch (item->getType()) {
			case FOG:    isFogActive = true; break;
			case SWORD:  isSwordActive = true; break;
			case SHIELD: isShieldActive = true; break;
			case HAMMER: isHammerActive = true; break;
		}
		
	}
	displayGameState();
}

/**
 * Pokrece glavnu petlju igre
 *
 * Funkcionalnost:
 * - Prikazuje stanje igre
 * - Prima i obradjuje korisnicki unos (WASD za kretanje, Q za izlaz)
 * - Upravlja kretanjem robota i minotaura
 * - Po zavrsetku igre generise izvjestaj
 */
void Game::start() {
	char command;
	while (!gameOver) {
		refresh();
		
		cout << endl << "Koristite WASD za kretanje robota, Q za izlaz iz igre " << endl;
		cout << "Unesite komandu: ";
		bool error = false;
		while (true) {
			command = tolower(_getch());
			if (command == 'q') {
				cout << "\nIzlaz iz programa..." << endl;
				gameOver = true;
				break;
			}
			else if (command == 'w' || command == 'a' || command == 's' || command == 'd') {
				try {
					handleRobotMovement(command);
					if (isMinotaurAlive) {
						handleMinotaurMovement();
					}
					break;
				}
				catch (const char* msg) {
					if (error) {
						cout << "\033[A\r";  // Pomjeri se za jedan red gore
						cout << "\033\r[K";  // Obrisi tu liniju
					}
					cout << "\033\r[K";  // Obrisi tu liniju
					cout << msg << endl;
					cout << "Unesite komandu:";
					//Sleep(700);
					error = true;
				}
			}
			else {
				if (error) {
					cout << "\033[A\r";  // Pomjeri se za jedan red gore
					cout << "\033\r[K";  // Obrisi tu liniju
				}
				cout << "\033\r[K";  // Obrisi tu liniju
				cout << "Nepoznata komanda, probajte ponovo!" << endl;
				cout << "Unesite komandu:";
				error = true;
			}
		}
	}
	ReportGenerator::generateReport(*this);
}

/**
 * Prikazuje trenutno stanje lavirinta i aktivnih predmeta
 *
 * Funkcionalnost:
 * - Ispisuje lavirint sa ili bez efekta magle
 * - Ispisuje sve aktivne predmete i njihovo preostalo trajanje
 */
void Game::displayGameState()
{
	cout << "Stanje igre:" << endl;
		
	// Ispis mape
	maze.printMaze(isFogActive);

	// Ispis aktivnih predmeta i duzinu trajanja
	cout << endl << "Broj predmeta: " << itemNumber << endl;
	cout << "Aktivni predmeti: " << endl;
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->getDuration() >= 0) {
			switch (items[i]->getType()) {
			case FOG:
				cout << "Magla rata: ";
				break;
			case SWORD:
				cout << "Mac: ";
				break;
			case SHIELD:
				cout << "Stit: ";
				break;
			case HAMMER:
				cout << "Cekic: ";
				break;
			}
			cout << "Trajanje jos: " << items[i]->getDuration() << endl;
		}

	}

}

/**
 * Vraca lavirint kao string
 *
 * @return string reprezentacija lavirinta
 */
string Game::getMazeString() const
{
	return maze.toString();
}

/**
 * Obradjuje kretanje robota u lavirintu
 *
 * Funkcionalnost:
 * - Pomera robota u smeru zadatom komandnom ('w', 'a', 's', 'd')
 * - Proverava prepreke (zid, ulaz, izlaz, minotaur)
 * - Upravlja razbijanjem zidova i skupljanjem predmeta
 * - Azurira stanje igre u slucaju izlaza, pobede ili poraza
 *
 * @param command karakter koji oznacava smer kretanja
 *
 * @throws const char* u slucaju neispravnog poteza (npr. zid na putu)
 */
void Game::handleRobotMovement(char command)
{
	// Trenutna pozicija robota
	int x, y;
	x = get<0>(maze.getRobotPosition());
	y = get<1>(maze.getRobotPosition());

	// Nova pozicija robota
	int newX, newY;
	newX = x;
	newY = y;

	if (command == 'w') {
		newX--;
	}
	else if (command == 'a') {
		newY--;
	}
	else if (command == 's') {
		newX++;
	}
	else if (command == 'd') {
		newY++;
	}

	// Provjera da li je na novoj poziciji zid
	if (maze.isWall(newX, newY)) {
		if (!isHammerActive) {
			throw "Na toj poziciji se nalazi zid!";
		}
		else if (newX == 0 || newY == 0 || newX == maze.getRows() - 1 || newY == maze.getColumns() - 1) {
			throw "Spoljasnji zidovi ne mogu biti razbijeni!";
		}
		else {
			// Razbijanje zida
			maze.brakeWall(newX, newY);
		}
	}
	else {
		// Provjera da li je na novoj poziciji predmet
		if (maze[newX][newY] == 'P') {
			int random = rand() % 4;
			Item* item;
			switch (random) {
				case 0:
					item = new FogItem();
					isFogActive = true;
					break;
				case 1:
					item = new SwordItem();
					isSwordActive = true;
					break;
				case 2:
					item = new ShieldItem();
					isShieldActive = true;
					break;
				case 3:
					item = new HammerItem();
					isHammerActive = true;
					break;
			}
			items.push_back(item);
			itemNumber--;

			// Postavljanje nove pozicije robota
			maze.moveRobot(newX, newY);
		}
		else if (maze[newX][newY] == 'U') {
			throw "Na toj poziciji se nalazi ulaz!";
		} 
		else if (maze[newX][newY] == 'I') {
			// Robot je stigao do izlaza
			cout << endl << endl << "Uspjesno ste stigli do izlaza iz lavirinta!" << endl;
			Sleep(1000);
			maze.moveRobot(newX, newY);
			gameOver = true;
			isWon = true;
		} 
		else if (maze[newX][newY] == 'M') {
			if (isSwordActive) {
				// Ubijen minotaur
				isMinotaurAlive = false;
				maze.moveRobot(newX, newY);
				maze.setMinotaurPosition(make_tuple(-1, -1)); // Minotaur je ubijen, postavljam ga van lavirinta
				return;
			}
			if (isMinotaurAlive) {
				gameOver = true;
				cout << endl << endl << "Napali ste minotaura bez maca, izgubili ste!" << endl;
				maze.killRobot();
				return;
			}
		}
		else {
			// Postavljanje nove pozicije robota
			maze.moveRobot(newX, newY);
		}	
	}
}

/**
 * Azurira stanje igre kada minotaur pojede robota
 *
 * Funkcionalnost:
 * - Unistava robota
 * - Pomera minotaura na novu poziciju
 * - Postavlja kraj igre
 *
 * @param x trenutni red minotaura
 * @param y trenutna kolona minotaura
 * @param newX nova pozicija reda
 * @param newY nova pozicija kolone
 */
void Game::foundRobot(int x, int y, int newX, int newY){
	maze.killRobot();
	maze.moveMinotaur(newX, newY);
	cout << endl << endl << "Izgubili ste, pojeo vas je minotaur!" << endl;
	gameOver = true;
}

/**
 * Obradjuje kretanje minotaura
 *
 * Funkcionalnost:
 * - Detektuje da li je robot u susednim poljima
 * - Napada robota ako nema aktivan stit
 * - Nasumicno bira sledece validno polje za kretanje
 * - Smanjuje broj predmeta ako minotaur prodje preko njih
 */
void Game::handleMinotaurMovement(){
	int x, y;
	x = get<0>(maze.getMinotaurPosition());
	y = get<1>(maze.getMinotaurPosition());

	int newX, newY;
	newX = x;
	newY = y;
		
	// Provjera da li je robot u blizini
	//bool foundRobot = false;

	// Pravljenje vectora mogucih polja i nesumican izbor novog polja
	vector<tuple<int, int>> possibleMoves;


	if (maze.canMinotaurMoveTo(x - 1, y)) {
		if (maze[x - 1][y] == 'R') {
			if (!isShieldActive) {
				foundRobot(x, y, x - 1, y);
				return;
			}
		}
		else {
			possibleMoves.push_back(make_tuple(x - 1, y));
		}
	}
	if (maze.canMinotaurMoveTo(x + 1, y)) {
		if (maze[x + 1][y] == 'R') {
			if (!isShieldActive) {
				foundRobot(x, y, x + 1, y);
				return;
			}
		}
		else {
			possibleMoves.push_back(make_tuple(x + 1, y));
		}
	}
	if (maze.canMinotaurMoveTo(x, y - 1)) {
		if (maze[x][y - 1] == 'R') {
			if (!isShieldActive) {
				foundRobot(x, y, x, y - 1);
				return;
			}
		}
		else {
			possibleMoves.push_back(make_tuple(x, y - 1));
		}
	}
	if (maze.canMinotaurMoveTo(x, y + 1)) {
		if (maze[x][y + 1] == 'R') {
			if (!isShieldActive) {
				foundRobot(x, y, x, y + 1);
				return;
			}
		}
		else {
			possibleMoves.push_back(make_tuple(x, y + 1));
		}
	}
		
	if (!possibleMoves.empty()) {
		int random = rand() % possibleMoves.size();
		newX = get<0>(possibleMoves[random]);
		newY = get<1>(possibleMoves[random]);

		// Unistavanje predmeta ako je minotaur na njemu
		if (maze.moveMinotaur(newX, newY)) {
			itemNumber--;
		}
	}
}

/**
 * Vraca broj preostalih predmeta u lavirintu
 *
 * @return broj preostalih predmeta
 */
int Game::getItemNumber(){
	return itemNumber;
}

/**
 * Vraca da li je igra pobijedjena
 *
 * @return true ako je robot stigao do izlaza, u suprotnom false
 */
bool Game::getResult()
{
	return isWon;
}

/**
 * Vraca trenutnu poziciju robota
 *
 * @return par (x, y) koji oznacava poziciju robota
 */
tuple<int, int> Game::getRobotPosition() const{
	return maze.getRobotPosition();
}

/**
 * Vraca trenutnu poziciju minotaura
 *
 * @return par (x, y) koji oznacava poziciju minotaura
 */
tuple<int, int> Game::getMinotaurPosition() const{
	return maze.getMinotaurPosition();
}