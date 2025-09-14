#pragma once
#include <set>
#include <tuple>
#include "Maze.h"

class MazeGenerator {
public:
	static void generateMaze(Maze& mazeClass, int itemNumber);

private:
	static void generateMazeWalls(char** mazeMatrix, int rows, int columns, std::tuple<int, int>& pStart);
	static bool findPath(char** maze, std::tuple<int, int>& start, std::set<std::tuple<int, int>>& visited);
};