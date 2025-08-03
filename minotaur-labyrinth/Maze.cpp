#include "Maze.h"
#include "maze_generator.h"
#include <iostream>

using namespace std;

Maze::Maze(int pRows, int pColumns, int itemNumber) {
	rows = pRows;
	columns = pColumns;
	
	mazeMatrix = new char* [rows];
	for (int i = 0; i < rows; i++) {
		mazeMatrix[i] = new char[columns];
	}
	generateMaze(mazeMatrix, pRows, pColumns, itemNumber, robotPosition, minotaurPosition);
}

Maze::Maze() {
	rows = 0;
	columns = 0;
	mazeMatrix = nullptr;
	robotPosition = make_tuple(0, 0);
	minotaurPosition = make_tuple(0, 0);
}

Maze::~Maze() {
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

void Maze::printMaze(bool isFogActive) const{
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

string Maze::toString() const{
	string retString = "";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			retString += mazeMatrix[i][j];
		}
		retString += "\n";
	}
	return retString;
}

bool Maze::isWall(int x, int y) const{
	if (x < 0 || x >= rows || y < 0 || y >= columns) {
		return true;
	}
	if (mazeMatrix[x][y] == '#') {
		return true;
	}
	return false;
}

bool Maze::canMinotaurMoveTo(int x, int y) const{
	if (x < 0 || x >= rows || y < 0 || y >= columns) {
		return false;
	}
	if (mazeMatrix[x][y] == '#' || mazeMatrix[x][y] == 'I' || mazeMatrix[x][y] == 'U') {
		return false;
	}
	return true;
}

void Maze::moveRobot(int x, int y) {
	mazeMatrix[get<0>(robotPosition)][get<1>(robotPosition)] = '.';
	mazeMatrix[x][y] = 'R';
	robotPosition = make_tuple(x, y);
}

bool Maze::moveMinotaur(int x, int y) {
	bool ret = false;
	mazeMatrix[get<0>(minotaurPosition)][get<1>(minotaurPosition)] = '.';
	if (mazeMatrix[x][y] == 'P'){
		ret = true; // Minotaur je pojeo predmet
	}
	mazeMatrix[x][y] = 'M';
	minotaurPosition = make_tuple(x, y);
	return ret;
}

void Maze::killMinotaur() {
	mazeMatrix[get<0>(minotaurPosition)][get<1>(minotaurPosition)] = '.';
	minotaurPosition = make_tuple(-1, -1); // Postavljam minotaura van lavirinta
}

void Maze::killRobot() {
	mazeMatrix[get<0>(robotPosition)][get<1>(robotPosition)] = '.';
	robotPosition = make_tuple(-1, -1); // Postavljam robota van lavirinta
}

void Maze::brakeWall(int x, int y) {
	mazeMatrix[x][y] = '.';
}

const char* Maze::operator[](int pRow) const {
	if (pRow < 0 || pRow >= rows) {
		throw std::out_of_range("Row index out of bounds");
	}
	return mazeMatrix[pRow];
}

int Maze::getRows() const{
	return rows;
}

int Maze::getColumns() const{
	return columns;
}

tuple<int, int> Maze::getRobotPosition() const{
	return robotPosition;
}

tuple<int, int> Maze::getMinotaurPosition() const{
	return minotaurPosition;
}

void Maze::setRobotPosition(tuple<int, int> newPosition) {
	robotPosition = newPosition;
}

void Maze::setMinotaurPosition(tuple<int, int> newPosition) {
	minotaurPosition = newPosition;
}