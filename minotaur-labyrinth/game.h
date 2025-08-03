#pragma once
#include "Maze.h"
#include "Item.h"
#include <vector>

using namespace std;

class Game {
private:
	Maze maze;
	int itemNumber;
	bool gameOver;
	bool isWon;
	bool isMinotaurAlive;
	vector<Item*> items;

	bool isFogActive = false;
	bool isSwordActive = false;
	bool isShieldActive = false;
	bool isHammerActive = false;
	
	void handleRobotMovement(char command); // Obrada unosa korisnika za robota
	void handleMinotaurMovement();         // Generisanje poteza Minotaura
	void foundRobot(int x, int y, int newX, int newY);			// Funkcija za jedenje robota od strane Minotaura
	//void handleItemPickup();               // Obrada kupljenja predmeta

public:
	Game(int rows, int columns, int itemNumber);
	~Game();

	void start();
	void refresh();
	void quit();
	void displayGameState();
	string getMazeString();

	Maze& getMaze();
	int getItemNumber();
	bool getResult();
	
};