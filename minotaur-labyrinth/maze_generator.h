#pragma once
#include <set>
#include <tuple>

using namespace std;

void generateMaze(char** mazeMatrix, int rows, int columns, int itemNumber);

void generateEmptyMaze(char** maze, int rows, int columns, tuple<int, int>& start);

void generateEmptyMaze(char** maze, int rows, int columns);

void generateInternalWalls(char** maze, int rows, int columns, set<tuple<int, int>> &visited);