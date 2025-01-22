#pragma once
#include <set>
#include <tuple>

using namespace std;

char** generateMaze(int rows, int columns, int itemNumber);

char** generateEmptyMaze(char** maze, int rows, int columns, tuple<int, int>& start);

char** generateEmptyMaze(char** maze, int rows, int columns);

char** generateInternalWalls(char** maze, int rows, int columns, set<tuple<int, int>> &visited);