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

	char** getMazeMatrix() const;
	int getRows() const;
	int getColumns() const;
	int getItemNumber() const;
	std::tuple<int, int> getRobotPosition() const;
	std::tuple<int, int> getMinotaurPosition() const;

	void setRobotPosition(std::tuple<int, int> newPosition);
	void setMinotaurPosition(std::tuple<int, int> newPosition);

	void moveRobot(int x, int y);
	void moveMinotaur(int x, int y);
	void brakeWall(int x, int y);

	void printMaze(bool isFogActive) const;
	std::string toString() const;
	bool isWall(int x, int y) const;
	bool canMinotaurMoveTo(int x, int y) const;

};
