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
	vector<Item*> items;
	
	void handleRobotMovement(char command); // Obrada unosa korisnika za robota
	void handleMinotaurMovement();         // Generisanje poteza Minotaura
	//void handleItemPickup();               // Obrada kupljenja predmeta

public:
	Game(int rows, int columns, int itemNumber);
	~Game();

	void start();
	void refresh();
	void quit();
	void displayGameState();
	string getMazeString();
	
};