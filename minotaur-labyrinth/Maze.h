/**
 * Maze.h
 *
 * Funkcionalnost:
 * - Definicija klase Maze koja predstavlja lavirint igre
 * - Sadrzi informacije o rasporedu elemenata u lavirintu, poziciji robota i minotaura
 * - Omogucava pomeranje entiteta, ispis lavirinta, detekciju zidova i druge osnovne operacije
 *
 * Autori: Ognjen [dodaj druge autore ako ih ima]
 * Datum poslednje izmene: avgust 2025
 */
#pragma once
#include <set>
#include <string>
#include <tuple>

class Maze {
private:
	char** mazeMatrix;                      // Matrica lavirinta (2D niz karaktera)
	int rows;                               // Broj redova lavirinta
	int columns;                            // Broj kolona lavirinta
	std::tuple<int, int> robotPosition;     // Pozicija robota u lavirintu (x, y)
	std::tuple<int, int> minotaurPosition;  // Pozicija minotaura u lavirintu (x, y)

public:
	Maze();
	Maze(int pRows, int pColumns, int itemNumber);
	~Maze();

	int getRows() const;
	int getColumns() const;
	std::tuple<int, int> getRobotPosition() const;
	std::tuple<int, int> getMinotaurPosition() const;
	const char* operator[](int row) const;

	void setRobotPosition(std::tuple<int, int> newPosition);
	void setMinotaurPosition(std::tuple<int, int> newPosition);

	void moveRobot(int x, int y);
	bool moveMinotaur(int x, int y);
	void killMinotaur();
	void killRobot();
	void brakeWall(int x, int y);

	void printMaze(bool isFogActive) const;
	std::string toString() const;
	bool isWall(int x, int y) const;
	bool canMinotaurMoveTo(int x, int y) const;

};
