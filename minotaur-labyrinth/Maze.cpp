#include "Maze.h"
#include "maze_generator.h"

Maze::Maze(int pRows, int pColumns, int pItemNumber) {
	itemNumber = pItemNumber;
	rows = pRows;
	columns = pColumns;
	mazeMatrix = generateMaze(pColumns, pRows, pItemNumber);
}

Maze::Maze() {
	rows = 0;
	columns = 0;
	itemNumber = 0;
	mazeMatrix = nullptr;
}

Maze::~Maze() {
	for (int i = 0; i < rows; i++) {
		delete[] mazeMatrix[i];
	}
	delete[] mazeMatrix;
}