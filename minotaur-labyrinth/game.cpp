#include <iostream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include "Game.h"
#include "Maze.h"
#include "maze_generator.h"

using namespace std;

Game::Game(int pRows, int pColumns, int pItemNumber)
	: itemNumber(pItemNumber),
	maze(pColumns, pRows, pItemNumber),
	gameOver(false) {}

Game::~Game() {
	//todo
}

void Game::start() {
	char command;
	while (!gameOver) {
		system("CLS");
		displayGameState();
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
					handleMinotaurMovement();
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
	// Ispis mape
	maze.printMaze();
	// Ispis broja predmeta i aktivnih predmeta
	cout << endl << "Broj predmeta: " << itemNumber << endl;
	//todo ispis aktivnih predmeta i duzinu trajanja

}

string Game::getMazeString() {
	//todo
	/*string mazeString = "";
	for (int i = 0; i < sizeof(mazeMatrix); i++) {
		for (int j = 0; j < sizeof(mazeMatrix[i]); j++) {
			mazeString += mazeMatrix[i][j];
		}
		mazeString += "\n";
	}
	return mazeString;*/
	return "todo";
}

// Funkcija za obradu kretanja robota
void Game::handleRobotMovement(char command) {
	// Trenutna pozicija robota
	int x, y;
	x = get<0>(maze.robotPosition);
	y = get<1>(maze.robotPosition);

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
		throw "Na toj poziciji se nalazi zid!";
	}
	else {
		// Provjera da li je na novoj poziciji predmet
		// todo efekat predmeta
		if (maze.mazeMatrix[newX][newY] == 'P') {
			itemNumber--;
		}
		else if (maze.mazeMatrix[newX][newY] == 'U') {
			throw "Na toj poziciji se nalazi ulaz!";
		} 
		else if (maze.mazeMatrix[newX][newY] == 'I') {
			//todo zapis stanja
			cout << endl << endl << "Pobjeda!" << endl;
			gameOver = true;
		}
		// Postavljanje nove pozicije robota
		maze.mazeMatrix[x][y] = '.';
		maze.mazeMatrix[newX][newY] = 'R';
		maze.robotPosition = make_tuple(newX, newY);
	}
}

void Game::handleMinotaurMovement() {
	int x, y;
	x = get<0>(maze.minotaurPosition);
	y = get<1>(maze.minotaurPosition);

	int newX, newY;
	newX = x;
	newY = y;

	// Provjera da li je robot u blizini
	bool foundRobot = false;

	// Pravljenje vectora mogucih polja i nesumican izbor novog polja
	vector<tuple<int, int>> possibleMoves;
	if (!maze.isWall(x - 1, y)) {
		if (maze.mazeMatrix[x - 1][y] == 'R') {
			foundRobot = true;
			newX = x - 1;
		}
		possibleMoves.push_back(make_tuple(x - 1, y));
	}
	if (!maze.isWall(x + 1, y)) {
		if (maze.mazeMatrix[x + 1][y] == 'R') {
			foundRobot = true;
			newX = x + 1;
		}
		possibleMoves.push_back(make_tuple(x + 1, y));
	}
	if (!maze.isWall(x, y - 1)) {
		if (maze.mazeMatrix[x][y - 1] == 'R') {
			foundRobot = true;
			newY = y - 1;
		}
		possibleMoves.push_back(make_tuple(x, y - 1));
	}
	if (!maze.isWall(x, y + 1)) {
		if (maze.mazeMatrix[x][y + 1] == 'R') {
			foundRobot = true;
			newY = y + 1;
		}
		possibleMoves.push_back(make_tuple(x, y + 1));
	}

	if (foundRobot) {
		//todo zapis stanja
		maze.mazeMatrix[x][y] = '.';
		maze.mazeMatrix[newX][newY] = 'M';
		cout << endl << endl << "Izgubili ste!" << endl;
		gameOver = true;
	}
	else {
		//todo random
		int random = rand() % possibleMoves.size();
		maze.mazeMatrix[x][y] = '.';
		maze.mazeMatrix[get<0>(possibleMoves[random])][get<1>(possibleMoves[random])] = 'M';
		maze.minotaurPosition = possibleMoves[random];

	}
}