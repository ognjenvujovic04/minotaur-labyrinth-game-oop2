#pragma once

using namespace std;

class Game {
public:
	Game(int rows, int columns, int itemNumber);
	~Game();

	void quit();
	
	char** mazeMatrix;
	int colomns, rows, itemNumber;



};