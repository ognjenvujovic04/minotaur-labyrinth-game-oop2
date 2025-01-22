#pragma once
#include <set>
#include <tuple>

using namespace std;

class Maze {
	//todo private geteri seteri
public:
	char** mazeMatrix;
	int itemNumber;
	int rows;
	int columns;
	tuple<int, int> robotPosition;
	tuple<int, int> minotaurPosition;

	Maze();
	Maze(int pRows, int pColumns, int pItemNumber);
	~Maze();

	void printMaze();
	bool isWall(int x, int y);
};

#pragma once
