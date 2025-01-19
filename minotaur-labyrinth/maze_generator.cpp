#include <iostream>
#include <ctime>

using namespace std;


char** generateInternalWalls(char** maze, int rows, int columns) {
	int wallNumber = (rows + columns) * 2 + rand() % (rows + columns);
	for (int i = 0; i < wallNumber; i++) {
		int wallX = rand() % (rows - 2) + 1;
		int wallY = rand() % (columns - 2) + 1;
		maze[wallX][wallY] = '#';
	}

	return maze;
}


char** generateMaze(int rows, int columns, int itemNumber) {
	char** maze = new char* [rows];
	for (int i = 0; i < rows; i++) {
		maze[i] = new char[columns];
	}
	// Spoljasni zidovi
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
				maze[i][j] = '#';
			}
			else {
				maze[i][j] = '.';
			}
		}
	}
	// Unutrasnji zidovi
	maze = generateInternalWalls(maze, rows, columns);
	// Ulaz
	int entrance = rand() % (columns - 2) + 1;
	maze[0][entrance] = 'U';
	// Izlaz
	int exit = rand() % (columns - 2) + 1;
	maze[rows - 1][exit] = 'I';
	// Robot
	maze[1][entrance] = 'R';
	// Minotaur
	int minotaurX = rand() % (rows - 2) + 1;
	int minotaurY = rand() % (columns - 2) + 1;
	maze[minotaurX][minotaurY] = 'M';
	// Predmeti
	for (int i = 0; i < itemNumber; i++) {
		int itemX = rand() % (rows - 2) + 1;
		int itemY = rand() % (columns - 2) + 1;
		maze[itemX][itemY] = 'P';
	}
	return maze;
}

