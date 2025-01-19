#include <iostream>
#include "maze_genearator.h"

using namespace std;

int main(){
	cout << "Dobrodosli u igricu bjeg iz lavirinta u Knososu!" << endl << endl;
	int columns, rows, item_number;
	cout << "Unesite broj kolona: ";
	cin >> columns;
	cout << "Unesite broj redova: ";
	cin >> rows;
	while (true){	
		cout << "Unesite broj predmeta: ";
		cin >> item_number;
		if (item_number > (columns * rows)/2){
			cout << "Broj predmeta ne moze biti veci od broja slobodnih polja lavirinta!" << endl;
		}
		else if(item_number <4) {
			cout << "Broj predmeta mora biti veci od 3!" << endl;
		}
		else {
			break;
		}
	}
	cout << "Igra pocinje!" << endl;
	char** maze = generateMaze(rows, columns, item_number);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cout << maze[i][j];
		}
		cout << endl;
	}
	


	
}