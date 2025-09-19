/**
 * MazeGenerator.cpp
 *
 * Funkcionalnost:
 * - Implementacija algoritma za generisanje lavirinta koristeci Primov algoritam.
 * - Provera postojanja putanje od pocetka do izlaza pomocu DFS pretrage.
 * - Generisanje polja za robota, minotaura i predmeta unutar lavirinta.
 *
 * Autori: Ognjen
 * Datum poslednje izjmene: 18.9.2025.
 */
#include <iostream>
#include <ctime>
#include <set>
#include <stack>
#include <vector>
#include <random>
#include <windows.h>
#include "MazeGenerator.h"
using namespace std;

/**
 * generateMazeWalls
 *
 * Funkcionalnost:
 * - Generise zidove lavirinta i prolaze koristeci Primov algoritam.
 * - Postavlja ulaz i izlaz lavirinta.
 *
 * Ulazni argumenti:
 * - char** mazeMatrix: 2D matrica lavirinta koja se popunjava.
 * - int rows: broj redova lavirinta.
 * - int columns: broj kolona lavirinta.
 * - tuple<int, int>& pStart: referenca za poziciju pocetnog ulaza (robot start).
 *
 * Povratna vrednost:
 * - Nema povratnu vrednost (void).
 */
void MazeGenerator::generateMazeWalls(char** mazeMatrix, int rows, int columns, tuple<int, int>& pStart) {
	// Inicijalizacija generatora ranodom brojeva
	random_device rd;
	mt19937 gen(rd());

	// Inicijalizacija matrice lavirinta samo sa zidovima
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			mazeMatrix[i][j] = '#';
		}
	}

	// Postavljanje granica lavirinta
	vector<tuple<int,int>> frontiers;
	vector<vector<bool>> visited(rows, vector<bool>(columns, false));

	int dx[] = { -2, 2, 0, 0 };
	int dy[] = { 0, 0, -2, 2 };

	int startRow = 1 + 2 * (gen() % ((rows - 1) / 2));
	int startCol = 1 + 2 * (gen() % ((columns - 1) / 2));

	// Oznacavanje pocetne pozicije
	mazeMatrix[startRow][startCol] = '.';
	visited[startRow][startCol] = true;

	// Dodavanje pocetne pozicije u frontiers
	for (int i = 0; i < 4; i++) {
		int newRow = startRow + dx[i];
		int newCol = startCol + dy[i];

		if (newRow > 0 && newRow < rows - 1 &&
			newCol > 0 && newCol < columns - 1 &&
			!visited[newRow][newCol]) {
			frontiers.push_back(make_tuple(newRow, newCol));
		}
	}

	// Glavina petlja Primovog algoritma
	while (!frontiers.empty()) {
		// Nesumican odabir iz frontiers
		uniform_int_distribution<> dis(0, static_cast<int>(frontiers.size() - 1));
		int randomIndex = dis(gen);
		tuple<int,int> current = frontiers[randomIndex];
		frontiers.erase(frontiers.begin() + randomIndex);
		
		// Provjera da li je trenutna pozicija vec posjecena
		if (visited[get<0>(current)][get<1>(current)]) {
			continue;
		}

		// Odredjivanje susjeda trenutne pozicije
		vector<tuple<int,int>> neighbors;
		for (int i = 0; i < 4; i++) {
			int adjRow = get<0>(current) + dx[i];
			int adjCol = get<1>(current) + dy[i];

			if (adjRow >= 0 && adjRow < rows &&
				adjCol >= 0 && adjCol < columns &&
				visited[adjRow][adjCol]) {
				neighbors.push_back(make_tuple(adjRow, adjCol));
			}
		}

		if (!neighbors.empty()) {
			// Nasumicno odaberi jednog susjeda
			uniform_int_distribution<> neighborDis(0, static_cast<int>(neighbors.size() - 1));
			tuple<int,int> neighbor = neighbors[neighborDis(gen)];

			// Napravi prolaz izmedju trenutne pozicije i susjeda
			mazeMatrix[get<0>(current)][get<1>(current)] = '.';
			visited[get<0>(current)][get<1>(current)] = true;

			int wallRow = (get<0>(current) + get<0>(neighbor)) / 2;
			int wallCol = (get<1>(current) + get<1>(neighbor)) / 2;
			mazeMatrix[wallRow][wallCol] = '.';

			// Dodaj polja u frontier
			for (int i = 0; i < 4; i++) {
				int newRow = get<0>(current) + dx[i];
				int newCol = get<1>(current) + dy[i];

				if (newRow > 0 && newRow < rows - 1 &&
					newCol > 0 && newCol < columns - 1 &&
					!visited[newRow][newCol]) {

					bool alreadyExists = false;
					for (const auto& frontier : frontiers) {
						if (get<0>(frontier) == newRow && get<1>(frontier) == newCol) {
							alreadyExists = true;
							break;
						}
					}

					if (!alreadyExists) {
						frontiers.push_back(make_tuple(newRow, newCol));
					}
				}
			}
		}
	}

	// Napravi ulaz nesumicno
	uniform_int_distribution<> entranceDis(1, columns - 2);
	int entranceCol = entranceDis(gen);
	mazeMatrix[0][entranceCol] = 'U';
	tuple<int, int> entrancePosition = make_tuple(1, entranceCol);
	pStart = entrancePosition;

	// Napravi izlaz nesumicno
	uniform_int_distribution<> exitDis(1, columns - 2);
	int exitCol = exitDis(gen);
	mazeMatrix[rows - 1][exitCol] = 'I';

	// Osiguraj prolaz
	mazeMatrix[rows - 2][exitCol] = '.';
	mazeMatrix[rows - 3][exitCol] = '.';
	

	// Ako je broj redova paran, predzadnju vrstu random promjeni u prolaze
	if (rows % 2 == 0 ) {
		for (int j = 1; j < columns - 1; j++) {
			int randomValue = rand() % 3; 
			if (mazeMatrix[rows - 2][j] == '#' && randomValue == 0) {
				mazeMatrix[rows - 2][j] = '.';
			}
		}
	}
	if (columns % 2 == 0){
	// Ako je broj kolona paran predzadnju kolonu ranodm promjeni u prolaze
		for (int j = 1; j < rows - 1; j++) {
			int randomValue = rand() % 3;
			if (mazeMatrix[j][columns - 2] == '#' && randomValue == 0) {
				mazeMatrix[j][columns - 2] = '.';
			}
		}
	}

	mazeMatrix[1][entranceCol] = 'R';
}

/**
 * findPath
 *
 * Funkcionalnost:
 * - Pronadje da li postoji putanja od startne pozicije do izlaza 'I' u lavirintu koristeci DFS (preko steka).
 * - Popunjava skup posecenih cvorova tokom pretrage.
 *
 * Ulazni argumenti:
 * - char** maze: 2D matrica lavirinta.
 * - tuple<int, int>& start: pozicija od koje pocinje pretraga.
 * - set<tuple<int, int>>& pVisited: referenca za skup posecenih cvorova.
 *
 * Povratna vrednost:
 * - bool: true ako postoji putanja do izlaza, false inace.
 */
bool MazeGenerator::findPath(char** maze, tuple<int, int>& start, set<tuple<int, int>>& pVisited) {
	bool pathExists = false;
	set<tuple<int, int>> visited;
	stack<tuple<int, int>> toVisit;
	toVisit.push(start);
	while (true) {
		if (toVisit.empty()) {
			pathExists = false;
			break;
		}
		tuple<int, int> current = toVisit.top();
		toVisit.pop();
		visited.insert(current);
		int x = get<0>(current);
		int y = get<1>(current);
		if (maze[x][y] == 'I') {
			pathExists = true;
			break;
		}
		if (x == 0 || y == 0) {
			continue;
		}
		if (maze[x - 1][y] != '#' && visited.find(make_tuple(x - 1, y)) == visited.end()) {
			toVisit.push(make_tuple(x - 1, y));
		}
		if (maze[x + 1][y] != '#' && visited.find(make_tuple(x + 1, y)) == visited.end()) {
			toVisit.push(make_tuple(x + 1, y));
		}
		if (maze[x][y - 1] != '#' && visited.find(make_tuple(x, y - 1)) == visited.end()) {
			toVisit.push(make_tuple(x, y - 1));
		}
		if (maze[x][y + 1] != '#' && visited.find(make_tuple(x, y + 1)) == visited.end()) {
			toVisit.push(make_tuple(x, y + 1));
		}
	}
	if (pathExists) {
		pVisited = visited;
		return true;
	} 
	else {
		return false;
	}
}

/**
 * generateMaze
 *
 * Funkcionalnost:
 * - Kreira lavirint pozivajuci generateMazeWalls i proverava putanju findPath.
 * - Postavlja poziciju robota na pocetak lavirinta.
 * - Nasumicno postavlja poziciju minotaura na dovoljnoj udaljenosti od robota.
 * - Nasumicno rasporedjuje predmete unutar lavirinta.
 * - Ispisuje lavirint i vreme generisanja.
 *
 * Ulazni argumenti:
 * - Maze& mazeClass: referenca na objekat klase Maze koji se popunjava.
 * - int itemNumber: broj predmeta za postavljanje.
 *
 * Povratna vrednost:
 * - Nema povratnu vrednost (void).
 */
void MazeGenerator::generateMaze(Maze& mazeClass, int itemNumber) {
	
	char** maze = mazeClass.mazeMatrix;

	// Mjerenje vremena generisanja
	clock_t begin = clock();

	// Uzimanje random seed-a
	srand(static_cast<unsigned int>(time(0)));

	// Posjecena polja
    set<tuple<int, int>> visited;

    tuple<int, int> start;

	// Zidovi i moguca polja
	generateMazeWalls(maze, mazeClass.rows, mazeClass.columns, start);

    if (findPath(maze, start, visited)) {
        cout << "Putanja do izlaza je pronadjena!" << endl;
    } else {
        cout << "Putanja do izlaza nije pronadjena!" << endl;
    }

    // Robot
    mazeClass.robotPosition = start;

	// Ispis stanja maze-a ali visited polja su zelene boje
	for (int i = 0; i < mazeClass.rows; i++) {
        for (int j = 0; j < mazeClass.columns; j++) {
            if (visited.find(make_tuple(i, j)) != visited.end()) {
                cout << "\033[1;32m" << maze[i][j] << "\033[0m";
            } else {
                cout << maze[i][j];
            }
        }
        cout << endl;
    }
    cout << endl;

	
	// Minotaur
	// Pravi vektor polja na kojima moze biti minotaur
	// gdje je minimalna udaljenost od robota 3 bloka
    vector<tuple<int, int>> possibleMinotaurPositions;
    for (auto& pos : visited) {
        if (abs(get<0>(pos) - get<0>(start)) + abs(get<1>(pos) - get<1>(start)) > 3) {
            possibleMinotaurPositions.push_back(pos);
        }
    }
    int minotaurIndex = rand() % possibleMinotaurPositions.size();
    mazeClass.minotaurPosition = possibleMinotaurPositions[minotaurIndex];
    maze[get<0>(mazeClass.minotaurPosition)][get<1>(mazeClass.minotaurPosition)] = 'M';


	// Generisanje predmeta
    int currentItems = 0;
    while (currentItems != itemNumber) {
        int itemX = rand() % (mazeClass.rows - 2) + 1;
        int itemY = rand() % (mazeClass.columns - 2) + 1;
        if (maze[itemX][itemY] == '.') {
            maze[itemX][itemY] = 'P';
            currentItems++;
        }
    }

	// Ispis vremena generisanja u sekundima
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    cout << endl << "Vrijeme generisanja: " << elapsed_secs << "s" << endl << endl;
    Sleep(3000);
}


