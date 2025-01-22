#include "Maze.h"
#include "maze_generator.h"
#include <iostream>


Maze::Maze(int pRows, int pColumns, int pItemNumber) {
	itemNumber = pItemNumber;
	rows = pRows;
	columns = pColumns;

	mazeMatrix = new char* [rows];
	for (int i = 0; i < rows; i++) {
		mazeMatrix[i] = new char[columns];
	}
	generateMaze(mazeMatrix,pRows, pColumns, pItemNumber);
}

Maze::Maze() {
	rows = 0;
	columns = 0;
	itemNumber = 0;
	mazeMatrix = nullptr;
}

Maze::~Maze() {
	cout << "Maze destructor called" << endl;
	if (mazeMatrix != nullptr) {
		for (int i = 0; i < rows; i++) {
			if (mazeMatrix[i] != nullptr) {
				delete[] mazeMatrix[i];
			}
		}
		delete[] mazeMatrix;
		mazeMatrix = nullptr;
	}
}

void Maze::printMaze() {
	if (!mazeMatrix) {
		cerr << "Maze matrix is null before calling printMaze!" << endl;
		return;
	}

	// Ulaz je smedje boje, izlaz je zelene boje, robot je plave boje
	// Minotaur je crvene boje, a predmeti su zute boje

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (mazeMatrix[i][j] == 'U') {
				std::cout << "\033[36m" << mazeMatrix[i][j] << "\033[0m";
			}
			else if (mazeMatrix[i][j] == 'I') {
				std::cout << "\033[32m" << mazeMatrix[i][j] << "\033[0m";
			}
			else if (mazeMatrix[i][j] == 'R') {
				std::cout << "\033[34m" << mazeMatrix[i][j] << "\033[0m";
			}
			else if (mazeMatrix[i][j] == 'M') {
				std::cout << "\033[31m" << mazeMatrix[i][j] << "\033[0m";
			}
			else if (mazeMatrix[i][j] == 'P') {
				std::cout << "\033[33m" << mazeMatrix[i][j] << "\033[0m";
			}
			else {
				std::cout << mazeMatrix[i][j];
			}
		}
		std::cout << std::endl;
	}

}