#include <iostream>
#include <windows.h>
#include "maze_genearator.h"
#include "game.h"

using namespace std;

//Adrese varijabli koje se koriste u funkcijama
void welcome(int& columns, int& rows, int& item_number) {
	cout << "Dobrodosli u igricu bjeg iz lavirinta u Knososu!" << endl << endl;
	cout << "Unesite broj kolona: ";
	cin >> columns;
	cout << "Unesite broj redova: ";
	cin >> rows;
	while (true) {
		cout << "Unesite broj predmeta: ";
		cin >> item_number;
		if (item_number > (columns * rows) / 2) {
			cout << "Broj predmeta ne moze biti veci od broja slobodnih polja lavirinta!" << endl;
		}
		else if (item_number < 4) {
			cout << "Broj predmeta mora biti veci od 3!" << endl;
		}
		else {
			break;
		}
	}
	cout << endl << "Igra pocinje za 3!" << endl;
	Sleep(1000);
	cout << "2!" << endl;
	Sleep(1000);
	cout << "1!" << endl;
	Sleep(1000);
	cout << "Sretno!" << endl;
	Sleep(500);

	//Brisanje teksta iz terminala
	system("CLS");
}

int main(){
	int columns, rows, item_number;

	welcome(columns, rows, item_number);
	
	Game game = Game(rows, columns, item_number);
	game.start();

}