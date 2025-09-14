/**
 * Maze.cpp
 *
 * Funkcionalnost:
 * - Implementacija lavirinta u kome se odvija igra
 * - Sadrzi metode za kretanje robota i minotaura, prikaz lavirinta i manipulaciju poljima
 *
 * Autori: Ognjen [dodati po potrebi]
 * Datum poslednje izmene: todo
 */
#include "Maze.h"
#include "MazeGenerator.h"
#include <iostream>

using namespace std;


/**
 * Konstruktor klase Maze
 *
 * Funkcionalnost:
 * - Alocira memoriju za matricu lavirinta
 * - Generise lavirint i postavlja robota i minotaura
 *
 * @param pRows broj redova lavirinta
 * @param pColumns broj kolona lavirinta
 * @param itemNumber broj predmeta u lavirintu
 */
Maze::Maze(int pRows, int pColumns, int itemNumber) {
	rows = pRows;
	columns = pColumns;
	
	mazeMatrix = new char* [rows];
	for (int i = 0; i < rows; i++) {
		mazeMatrix[i] = new char[columns];
	}
	MazeGenerator::generateMaze(*this, itemNumber);
}

/**
 * Podrazumevani konstruktor
 *
 * Funkcionalnost:
 * - Postavlja prazne vrednosti i nulira pokazivace
 */
Maze::Maze() {
	rows = 0;
	columns = 0;
	mazeMatrix = nullptr;
	robotPosition = make_tuple(0, 0);
	minotaurPosition = make_tuple(0, 0);
}

/**
 * Destruktor klase Maze
 *
 * Funkcionalnost:
 * - Oslobadja dinamicki alociranu memoriju za matricu lavirinta
 */
Maze::~Maze() {
	if (mazeMatrix != nullptr) {
		for (int i = 0; i < rows; i++) {
			if (mazeMatrix[i] != nullptr) {
				delete[] mazeMatrix[i];
			}
		}
		delete[] mazeMatrix;
		mazeMatrix = nullptr;
	}
}

/**
 * Prikazuje lavirint na standardnom izlazu
 *
 * @param isFogActive ako je true, smanjuje vidljivost na 3x3 polja oko robota
 */
void Maze::printMaze(bool isFogActive) const{
	if (!mazeMatrix) {
		cerr << "Maze matrix is null before calling printMaze!" << endl;
		return;
	}

	// Ulaz je smedje boje, izlaz je zelene boje, robot je plave boje
	// Minotaur je crvene boje, a predmeti su zute boje

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (isFogActive) {
				if (i < get<0>(robotPosition) - 1 || i > get<0>(robotPosition) + 1 || j < get<1>(robotPosition) - 1 || j > get<1>(robotPosition) + 1) {
					cout << "*";
					continue;
				}
			}
			if (mazeMatrix[i][j] == 'U') {
				std::cout << "\033[36m" << mazeMatrix[i][j] << "\033[0m";
			}
			else if (mazeMatrix[i][j] == 'I') {
				std::cout << "\033[32m" << mazeMatrix[i][j] << "\033[0m";
			}
			else if (mazeMatrix[i][j] == 'R') {
				std::cout << "\033[34m" << mazeMatrix[i][j] << "\033[0m";
			}
			else if (mazeMatrix[i][j] == 'M') {
				std::cout << "\033[31m" << mazeMatrix[i][j] << "\033[0m";
			}
			else if (mazeMatrix[i][j] == 'P') {
				std::cout << "\033[33m" << mazeMatrix[i][j] << "\033[0m";
			}
			else {
				std::cout << mazeMatrix[i][j];
			}
		}
		std::cout << std::endl;
	}

}

/**
 * Vraca string reprezentaciju lavirinta
 *
 * @return lavirint kao string
 */
string Maze::toString() const {
	string retString = "";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			retString += mazeMatrix[i][j];
		}
		retString += "\n";
	}
	return retString;
}

/**
 * Proverava da li je zadato polje zid
 *
 * @param x red
 * @param y kolona
 * @return true ako je polje zid ili van granica, u suprotnom false
 */
bool Maze::isWall(int x, int y) const{
	if (x < 0 || x >= rows || y < 0 || y >= columns) {
		return true;
	}
	if (mazeMatrix[x][y] == '#') {
		return true;
	}
	return false;
}

/**
 * Proverava da li minotaur moze da se pomeri na zadato polje
 *
 * @param x red
 * @param y kolona
 * @return true ako moze da se pomeri, u suprotnom false
 */
bool Maze::canMinotaurMoveTo(int x, int y) const{
	if (x < 0 || x >= rows || y < 0 || y >= columns) {
		return false;
	}
	if (mazeMatrix[x][y] == '#' || mazeMatrix[x][y] == 'I' || mazeMatrix[x][y] == 'U') {
		return false;
	}
	return true;
}

/**
 * Pomera robota na zadatu poziciju
 *
 * @param x novi red
 * @param y nova kolona
 */
void Maze::moveRobot(int x, int y){
	mazeMatrix[get<0>(robotPosition)][get<1>(robotPosition)] = '.';
	mazeMatrix[x][y] = 'R';
	robotPosition = make_tuple(x, y);
}

/**
 * Pomera minotaura na zadatu poziciju
 *
 * @param x novi red
 * @param y nova kolona
 * @return true ako je minotaur pojeo predmet, u suprotnom false
 */
bool Maze::moveMinotaur(int x, int y) {
	bool ret = false;
	mazeMatrix[get<0>(minotaurPosition)][get<1>(minotaurPosition)] = '.';
	if (mazeMatrix[x][y] == 'P'){
		ret = true; // Minotaur je pojeo predmet
	}
	mazeMatrix[x][y] = 'M';
	minotaurPosition = make_tuple(x, y);
	return ret;
}

/**
 * Ubija minotaura i uklanja ga iz lavirinta
 *
 * Funkcionalnost:
 * - Postavlja polje minotaura na prazan karakter
 * - Postavlja poziciju minotaura van lavirinta
 */
void Maze::killMinotaur() {
	mazeMatrix[get<0>(minotaurPosition)][get<1>(minotaurPosition)] = '.';
	minotaurPosition = make_tuple(-1, -1); // Postavljam minotaura van lavirinta
}

/**
 * Ubija robota i uklanja ga iz lavirinta
 *
 * Funkcionalnost:
 * - Postavlja polje robota na prazan karakter
 * - Postavlja poziciju robota van lavirinta
 */
void Maze::killRobot() {
	mazeMatrix[get<0>(robotPosition)][get<1>(robotPosition)] = '.';
	robotPosition = make_tuple(-1, -1); // Postavljam robota van lavirinta
}

/**
 * Brise zid na zadatom polju
 *
 * @param x red
 * @param y kolona
 */
void Maze::brakeWall(int x, int y) {
	mazeMatrix[x][y] = '.';
}

/**
 * Operator za pristup redovima lavirinta
 *
 * @param pRow red koji se pristupa
 * @return pokazivac na string koji predstavlja red
 * @throws std::out_of_range ako je red van granica
 */
const char* Maze::operator[](int pRow) const {
	if (pRow < 0 || pRow >= rows) {
		throw std::out_of_range("Row index out of bounds");
	}
	return mazeMatrix[pRow];
}

/**
 * Vraca broj redova lavirinta
 *
 * @return broj redova
 */
int Maze::getRows() const{
	return rows;
}

/**
 * Vraca broj kolona lavirinta
 *
 * @return broj kolona
 */
int Maze::getColumns() const
{
	return columns;
}

/**
 * Vraca trenutnu poziciju robota
 *
 * @return tuple (x, y) pozicija robota
 */
tuple<int, int> Maze::getRobotPosition() const{
	return robotPosition;
}

/**
 * Vraca trenutnu poziciju minotaura
 *
 * @return tuple (x, y) pozicija minotaura
 */
tuple<int, int> Maze::getMinotaurPosition() const{
	return minotaurPosition;
}

/**
 * Postavlja novu poziciju robota
 *
 * @param newPosition tuple (x, y) nova pozicija
 */
void Maze::setRobotPosition(tuple<int, int> newPosition){
	robotPosition = newPosition;
}

/**
 * Postavlja novu poziciju minotaura
 *
 * @param newPosition tuple (x, y) nova pozicija
 */
void Maze::setMinotaurPosition(tuple<int, int> newPosition) {
	minotaurPosition = newPosition;
}