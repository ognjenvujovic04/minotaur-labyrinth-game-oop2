#pragma once
#include <set>
#include <tuple>

class MazeGenerator {
public:
	static void generateMaze(char** mazeMatrix, int rows, int columns, int itemNumber, std::tuple<int, int>& robotPosition, std::tuple<int, int>& minotaurPosition);

private:
	static void generateMazeWalls(char** mazeMatrix, int rows, int columns, std::tuple<int, int>& pStart);
	static bool findPath(char** maze, int rows, int columns, std::tuple<int, int>& start, std::set<std::tuple<int, int>>& visited);
};