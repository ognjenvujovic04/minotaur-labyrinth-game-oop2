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
	generateMaze(mazeMatrix, pRows, pColumns, pItemNumber, robotPosition, minotaurPosition);
}

Maze::Maze() {
	rows = 0;
	columns = 0;
	itemNumber = 0;
	mazeMatrix = nullptr;
	robotPosition = make_tuple(0, 0);
	minotaurPosition = make_tuple(0, 0);
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

void Maze::printMaze(bool isFogActive) {
	if (!mazeMatrix) {
		cerr << "Maze matrix is null before calling printMaze!" << endl;
		return;
	}

	// Ulaz je smedje boje, izlaz je zelene boje, robot je plave boje
	// Minotaur je crvene boje, a predmeti su zute boje

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (isFogActive) {
				if (i < get<0>(robotPosition) - 1 || i > get<0>(robotPosition) + 1 || j < get<1>(robotPosition) - 1 || j > get<1>(robotPosition) + 1) {
					cout << "*";
					continue;
				}
			}
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

string Maze::toString() {
	string retString = "";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			retString += mazeMatrix[i][j];
		}
		retString += "\n";
	}
	return retString;
}

bool Maze::isWall(int x, int y) {
	if (x < 0 || x >= rows || y < 0 || y >= columns) {
		return true;
	}
	if (mazeMatrix[x][y] == '#') {
		return true;
	}
	return false;
}

bool Maze::canMinotaurMoveTo(int x, int y) {
	if (x < 0 || x >= rows || y < 0 || y >= columns) {
		return false;
	}
	if (mazeMatrix[x][y] == '#' || mazeMatrix[x][y] == 'I' || mazeMatrix[x][y] == 'U') {
		return false;
	}
	return true;
}

char** Maze::getMazeMatrix() {
	return mazeMatrix;
}

int Maze::getRows() {
	return rows;
}

int Maze::getColumns() {
	return columns;
}

int Maze::getItemNumber() {
	return itemNumber;
}

tuple<int, int> Maze::getRobotPosition() {
	return robotPosition;
}

tuple<int, int> Maze::getMinotaurPosition() {
	return minotaurPosition;
}

void Maze::setRobotPosition(tuple<int, int> newPosition) {
	robotPosition = newPosition;
}

void Maze::setMinotaurPosition(tuple<int, int> newPosition) {
	minotaurPosition = newPosition;
}