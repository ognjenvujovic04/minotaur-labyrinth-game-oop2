#pragma once
#include <set>
#include <tuple>

using namespace std;

void generateMaze(char** mazeMatrix, int rows, int columns, int itemNumber, tuple<int, int>& robotPosition, tuple<int, int>& minotaurPosition);

void generateEmptyMaze(char** maze, int rows, int columns, tuple<int, int>& start);

void generateWalls(char** maze, int rows, int columns, set<tuple<int, int>> &visited, tuple<int, int> &start);