#pragma once
#include "Maze.h"
#include "Item.h"
/**
 * Game.h
 *
 * Funkcionalnost:
 * - Definicija klase Game koja upravlja cijelokupnom igrom
 * - Sadrži atribute za stanje lavirinta, robota, minotaura i aktivne predmete
 * - Deklaracije metoda za logiku igre i prikaz stanja
 *
 * Autori: Ognjen [dodati po potrebi]
 * Datum poslednje izmene: todo
 */
#include <vector>

class Game {
private:
	Maze maze;                     // Lavirint u kojem se odvija igra
	int itemNumber;               // Broj preostalih predmeta u lavirintu
	bool gameOver;                // Oznacava da li je igra zavrsena
	bool isWon;                   // Oznacava da li je igrac pobedio
	bool isMinotaurAlive;        // Status zivota minotaura
	std::vector<Item*> items;    // Lista aktivnih predmeta u igri

	bool isFogActive = false;    // Da li je aktivan efekat magle
	bool isSwordActive = false;  // Da li je aktivan efekat maca
	bool isShieldActive = false; // Da li je aktivan efekat stita
	bool isHammerActive = false; // Da li je aktivan efekat cekica
	
	void handleRobotMovement(char command); 
	void handleMinotaurMovement();         
	void foundRobot(int x, int y, int newX, int newY);			

public:
	Game(int rows, int columns, int itemNumber);
	~Game();

	void start();
	void refresh();
	void displayGameState();
	std::string getMazeString() const;

	std::tuple<int, int> getRobotPosition() const;
	std::tuple<int, int> getMinotaurPosition() const;
	int getItemNumber();
	bool getResult();
	
};