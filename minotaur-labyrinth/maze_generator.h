#pragma once
#include <set>
#include <tuple>

void generateMaze(char** mazeMatrix, int rows, int columns, int itemNumber, std::tuple<int, int>& robotPosition, std::tuple<int, int>& minotaurPosition);

void generateEmptyMaze(char** maze, int rows, int columns, std::tuple<int, int>& start, std::tuple<int, int>& end);

void generateWalls(char** maze, int rows, int columns, std::set<std::tuple<int, int>> &visited, std::tuple<int, int> &start);