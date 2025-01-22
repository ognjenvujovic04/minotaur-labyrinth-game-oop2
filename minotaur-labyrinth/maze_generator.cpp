#include <iostream>
#include <ctime>
#include <set>
#include <queue>
#include "maze_generator.h"

using namespace std;

void generateEmptyMaze(char** maze, int rows, int columns, tuple<int,int> &start) {
	// Spoljasnji zidovi
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
				maze[i][j] = '#';
			}
			else {
				maze[i][j] = '.';
			}
		}
	}
	// Ulaz i robot
	int entrance = rand() % (columns - 2) + 1;
	maze[0][entrance] = 'U';
	maze[1][entrance] = 'R';
	start = make_tuple(1, entrance);
	// Izlaz
	int exit = rand() % (columns - 2) + 1;
	maze[rows - 1][exit] = 'I';

}

void generateEmptyMaze(char** maze, int rows, int columns) {
	// Spoljasnji zidovi
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0 || i == rows - 1 || j == 0 || j == columns - 1) {
				maze[i][j] = '#';
			}
			else {
				maze[i][j] = '.';
			}
		}
	}
	// Ulaz i robot
	int entrance = rand() % (columns - 2) + 1;
	maze[0][entrance] = 'U';
	maze[1][entrance] = 'R';
	// Izlaz
	int exit = rand() % (columns - 2) + 1;
	maze[rows - 1][exit] = 'I';

}



void generateInternalWalls(char** maze, int rows, int columns, set<tuple<int, int>> &pVisited) {
	//Provjera da li postoji putanja od ulaza do izlaza i zapis u path
	

	// Pocetna lokacija robota
	tuple<int, int> start;

	// Generisanje zidova i provjera da li postoji putanja
	while (true) {
		generateEmptyMaze(maze, rows, columns, start);
		// todo ne samo minimalno
		int wallNumber = (rows + columns) * 2;
		//int wallNumber = (rows + columns) * 2 + rand() % ((rows + columns) / 2);
		while (wallNumber != 0) {
			int wallX = rand() % (rows - 2) + 1;
			int wallY = rand() % (columns - 2) + 1;
			if (maze[wallX][wallY] == 'R') {
				continue;
			}
			maze[wallX][wallY] = '#';
			wallNumber--;
		}
		// Provjera postojanja putanje
		bool pathExists = true;
		set<tuple<int, int>> visited;
		queue<tuple<int, int>> toVisit;
		toVisit.push(start);
		while (true) {
			if (toVisit.empty()) {
				pathExists = false;
				break;
			}
			tuple<int, int> current = toVisit.front();
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
			break;
		}
	}
}


//char** generateMaze(int rows, int columns, int itemNumber) {
void generateMaze(char** maze, int rows, int columns, int itemNumber) {
	// Mjerenje vremena generisanja
	clock_t begin = clock();

	// Uzimanje random seed-a
	srand(time(0));

	// Prazan lavirint
	generateEmptyMaze(maze, rows, columns);
	
	
	// Posjecena polja
	set<tuple<int, int>> visited;

	tuple<int, int> start;
	// todo Vrijeme genersianja putanje	
	// Unutrasnji zidovi i put
	generateInternalWalls(maze, rows, columns, visited);

	// Ispis stanja maze-a ali visited polja su zelene boje

	/*for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (visited.find(make_tuple(i, j)) != visited.end()) {
				cout << "\033[1;32m" << maze[i][j] << "\033[0m";
			}
			else {
				cout << maze[i][j];
			}
			if (maze[i][j] == 'R') {
				start = make_tuple(i, j);
			}
		}
		cout << endl;
	}
	cout << endl;*/

	// Minotaur
	// Pravi vektor polja na kojima moze biti minotaur
	// gdje je minimalna udaljenost od robota 3 bloka
	vector<tuple<int, int>> possibleMinotaurPositions;
	for (auto it = visited.begin(); it != visited.end(); it++) {
		if (abs(get<0>(*it) - get<0>(start)) + abs(get<1>(*it) - get<1>(start)) > 3) {
			possibleMinotaurPositions.push_back(*it);
		}
	}
	int minotaurIndex = rand() % possibleMinotaurPositions.size();
	tuple<int, int> minotaurPosition = possibleMinotaurPositions[minotaurIndex];
	maze[get<0>(minotaurPosition)][get<1>(minotaurPosition)] = 'M';
	

	// Predmeti todo
	/*for (int i = 0; i < itemNumber; i++) {
		int itemX = rand() % (rows - 2) + 1;
		int itemY = rand() % (columns - 2) + 1;
		maze[itemX][itemY] = 'P';
	}*/

	// Ispis vremena generisanja u sekundima
	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
	cout << endl << "Vrijeme generisanja: " << elapsed_secs << "s" << endl << endl;
}

