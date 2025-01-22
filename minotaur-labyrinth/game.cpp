#include <iostream>
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
		displayGameState();
		cout << endl <<  "Koristite WASD za kretanje robota, Q za izlaz iz igre: ";
		cout << "Unesite komandu: ";
		cin >> command;
		if (command == 'Q') {
			quit();
		}
		else {
			/*handleRobotMovement(command);
			handleMinotaurMovement();*/
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