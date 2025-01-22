#pragma once
#include "Maze.h"

using namespace std;

class Game {
private:
	Maze maze;
	int itemNumber;
	//Robot robot;
	//Minotaur minotaur;
	bool gameOver;
	
	void handleRobotMovement(char command); // Obrada unosa korisnika za robota
	//void handleMinotaurMovement();         // Generisanje poteza Minotaura
	//void handleItemPickup();               // Obrada podizanja predmeta

public:
	Game(int rows, int columns, int itemNumber);
	~Game();

	void start();
	void quit();
	void displayGameState();
	string getMazeString();
	
};