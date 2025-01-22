#pragma once
#include <set>
#include <string>
#include <tuple>

using namespace std;

class Maze {
private:
	char** mazeMatrix;
	int itemNumber;
	int rows;
	int columns;
	tuple<int, int> robotPosition;
	tuple<int, int> minotaurPosition;

public:
	Maze();
	Maze(int pRows, int pColumns, int pItemNumber);
	~Maze();

	char** getMazeMatrix();
	int getRows();
	int getColumns();
	int getItemNumber();
	tuple<int, int> getRobotPosition();
	tuple<int, int> getMinotaurPosition();

	void setRobotPosition(tuple<int, int> newPosition);
	void setMinotaurPosition(tuple<int, int> newPosition);

	void moveRobot(int x, int y);
	void moveMinotaur(int x, int y);
	void brakeWall(int x, int y);

	void printMaze(bool isFogActive);
	string toString();
	bool isWall(int x, int y);
	bool canMinotaurMoveTo(int x, int y);

};
