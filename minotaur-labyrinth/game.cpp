#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "Game.h"
#include "Item.h"
#include "FogItem.h"
#include "SwordItem.h"
#include "ShieldItem.h"
#include "HammerItem.h"
#include "Maze.h"
#include "maze_generator.h"

using namespace std;

Game::Game(int pRows, int pColumns, int pItemNumber)
	: itemNumber(pItemNumber),
	maze(pColumns, pRows, pItemNumber),
	gameOver(false),
	items(), 
	isMinotaurAlive(true){ }
	

Game::~Game() {
	//todo
}

void Game::refresh() {
	system("CLS");
	for (Item* item : items) {
		if (item->getDuration() == 0) {
			// todo mozda i nece trebati ako svaki put ucitavam efekte
			//item->resetEffect();
			items.erase(remove(items.begin(), items.end(), item), items.end());
			delete item;
		}
		else {
			item->decreaseDuration();
		}
	}
	displayGameState();
}

void Game::start() {
	char command;
	while (!gameOver) {
		refresh();
		
		cout << endl << "Koristite WASD za kretanje robota, Q za izlaz iz igre " << endl;
		cout << "Unesite komandu: ";
		bool error = false;
		while (true) {
			command = tolower(_getch());
			//todo strijelice
			if (command == 'q') {
				//todo zapis stanja
				cout << " Izlaz iz programa" << endl;
				Sleep(700);
				gameOver = true;
				break;
			}
			else if (command == 'w' || command == 'a' || command == 's' || command == 'd') {
				try {
					handleRobotMovement(command);
					// todo popravljanje refreshe rate
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
				//Sleep(700);
				error = true;
			}
		}
	}
}
		

void Game::quit() {
	gameOver = true;
	//Todo zapis stanja
}

void Game::displayGameState() {
	cout << "Stanje igre:" << endl;

	// Provera da li je aktivna magla rata
	bool isFogActive = false;
	for (const Item* item : items) {
		if (item->getType() == FOG && item->getDuration() > 0) {
			isFogActive = true;
			break;
		}
	}

	// Ispis mape
	maze.printMaze(isFogActive);

	// Ispis aktivnih predmeta i duzinu trajanja
	cout << endl << "Broj predmeta: " << itemNumber << endl;
	cout << "Aktivni predmeti: " << endl;
	for (int i = 0; i < items.size(); i++) {
		if (items[i]->getDuration() > 0) {
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

string Game::getMazeString() {
	return maze.toString();
}

// Funkcija za obradu kretanja robota
void Game::handleRobotMovement(char command) {
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
		// Da li je aktiviran cekic
		bool isHammerActive = false;
		for (Item* item : items) {
			if (item->getType() == HAMMER && item->getDuration() > 0) {
				isHammerActive = true;
				break;
			}
		}
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
		if (maze.getMazeMatrix()[newX][newY] == 'P') {
			int random = rand() % 4;
			Item* item;
			switch (random) {
				case 0:
					item = new FogItem();
					break;
				case 1:
					item = new SwordItem();
					break;
				case 2:
					item = new ShieldItem();
					break;
				case 3:
					item = new HammerItem();
					break;
			}
			items.push_back(item);
			itemNumber--;

			// Postavljanje nove pozicije robota
			maze.moveRobot(newX, newY);
		}
		else if (maze.getMazeMatrix()[newX][newY] == 'U') {
			throw "Na toj poziciji se nalazi ulaz!";
		} 
		else if (maze.getMazeMatrix()[newX][newY] == 'I') {
			//todo zapis stanja
			cout << endl << endl << "Pobjeda!" << endl;
			gameOver = true;
		} 
		else if (maze.getMazeMatrix()[newX][newY] == 'M') {
			for (Item* item : items) {
				if (item->getType() == SWORD && item->getDuration() > 0) {
					// Ubijen minotaur
					isMinotaurAlive = false;
					maze.moveRobot(newX, newY);
					return;
				}
			}
			if (isMinotaurAlive) {
				gameOver = true;
				cout << endl << endl << "Napali ste minotaura bez maca, izgubili ste!" << endl;
				maze.getMazeMatrix()[x][y] = '.';
				return;
			}
		}
		else {
			// Postavljanje nove pozicije robota
			maze.moveRobot(newX, newY);
		}	
	}
}

// Funkcija za generisanje poteza Minotaura
void Game::handleMinotaurMovement() {
	int x, y;
	x = get<0>(maze.getMinotaurPosition());
	y = get<1>(maze.getMinotaurPosition());

	int newX, newY;
	newX = x;
	newY = y;

	// Provjera da li je stit aktivan
	bool isShieldActive = false;
	for (Item* item : items) {
		if (item->getType() == SHIELD && item->getDuration() > 0) {
			isShieldActive = true;
			break;
		}
	}

	// Provjera da li je robot u blizini
	bool foundRobot = false;

	// Pravljenje vectora mogucih polja i nesumican izbor novog polja
	vector<tuple<int, int>> possibleMoves;


	if (maze.canMinotaurMoveTo(x - 1, y)) {
		if (maze.getMazeMatrix()[x - 1][y] == 'R') {
			if (!isShieldActive) {
				foundRobot = true;
				newX = x - 1;
				possibleMoves.push_back(make_tuple(x - 1, y));
			}
		}
		else {
			possibleMoves.push_back(make_tuple(x - 1, y));
		}
	}
	if (maze.canMinotaurMoveTo(x + 1, y)) {
		if (maze.getMazeMatrix()[x + 1][y] == 'R') {
			if (!isShieldActive) {
				foundRobot = true;
				newX = x + 1;
				possibleMoves.push_back(make_tuple(x + 1, y));
			}
		}
		else {
			possibleMoves.push_back(make_tuple(x + 1, y));
		}
	}
	if (maze.canMinotaurMoveTo(x, y - 1)) {
		if (maze.getMazeMatrix()[x][y - 1] == 'R') {
			if (!isShieldActive) {
				foundRobot = true;
				newY = y - 1;
				possibleMoves.push_back(make_tuple(x, y - 1));
			}
		}
		else {
			possibleMoves.push_back(make_tuple(x, y - 1));
		}
	}
	if (maze.canMinotaurMoveTo(x, y + 1)) {
		if (maze.getMazeMatrix()[x][y + 1] == 'R') {
			if (!isShieldActive) {
				foundRobot = true;
				newY = y + 1;
				possibleMoves.push_back(make_tuple(x, y + 1));
			}
		}
		else {
			possibleMoves.push_back(make_tuple(x, y + 1));
		}
	}

	if (foundRobot) {
		//todo zapis stanja
		maze.getMazeMatrix()[x][y] = '.';
		maze.getMazeMatrix()[newX][newY] = 'M';
		cout << endl << endl << "Izgubili ste, pojeo vas je minotaur!" << endl;
		gameOver = true;
	}
	else {
		// todo sta ako satjeram minotaura u cosak
		// mozda da gurne robota
		int random = rand() % possibleMoves.size();
		maze.getMazeMatrix()[x][y] = '.';
		maze.getMazeMatrix()[get<0>(possibleMoves[random])][get<1>(possibleMoves[random])] = 'M';
		maze.setMinotaurPosition(possibleMoves[random]);

	}
}