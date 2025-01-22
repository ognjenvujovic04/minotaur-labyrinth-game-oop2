#include <iostream>
#include "Game.h"
#include "Maze.h"
#include "maze_generator.h"

using namespace std;

Game::Game(int pRows, int pColumns, int pItemNumber) {
	itemNumber = pItemNumber;
	maze = Maze(pColumns, pRows, pItemNumber);
	gameOver = false;
}

Game::~Game() {
	//todo
}

void Game::start() {
	char command;
	while (!gameOver) {
		displayGameState();
		cout << "Koristite WASD za kretanje robota, Q za izlaz iz igre: ";
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
	// todo ispis mape
	/*for (int i = 0; i < sizeof(maze); i++) {
		for (int j = 0; j < sizeof(mazeMatrix[i]); j++) {
			cout << mazeMatrix[i][j]<< " ";
		}
		cout << endl;
	}
	cout << endl;*/
	//ispist broja predmeta i aktivnih predmeta
	cout << "Broj predmeta: " << itemNumber << endl;
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