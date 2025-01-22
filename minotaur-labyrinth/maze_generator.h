#pragma once
#include <set>
#include <tuple>

using namespace std;

//class Maze {
//	//todo private geteri seteri
//public:
//	char** mazeMatrix;
//	int itemNumber;
//	int rows;
//	int columns;
//	tuple<int, int> robotPosition;
//
//	Maze(char** mazeMatrix ,int pRows, int pColumns, int pItemNumber);
//	~Maze();
//};


char** generateMaze(int rows, int columns, int itemNumber);

char** generateEmptyMaze(char** maze, int rows, int columns, tuple<int, int>& start);

char** generateEmptyMaze(char** maze, int rows, int columns);

char** generateInternalWalls(char** maze, int rows, int columns, set<tuple<int, int>> &visited);