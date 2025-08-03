#pragma once
#include <set>
#include <string>
#include <tuple>

class Maze {
private:
	char** mazeMatrix;
	int itemNumber;
	int rows;
	int columns;
	std::tuple<int, int> robotPosition;
	std::tuple<int, int> minotaurPosition;

public:
	Maze();
	Maze(int pRows, int pColumns, int pItemNumber);
	~Maze();

	char** getMazeMatrix();
	int getRows();
	int getColumns();
	int getItemNumber();
	std::tuple<int, int> getRobotPosition();
	std::tuple<int, int> getMinotaurPosition();

	void setRobotPosition(std::tuple<int, int> newPosition);
	void setMinotaurPosition(std::tuple<int, int> newPosition);

	void moveRobot(int x, int y);
	void moveMinotaur(int x, int y);
	void brakeWall(int x, int y);

	void printMaze(bool isFogActive);
	std::string toString();
	bool isWall(int x, int y);
	bool canMinotaurMoveTo(int x, int y);

};
