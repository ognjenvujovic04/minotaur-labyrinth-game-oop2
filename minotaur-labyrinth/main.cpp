#include <iostream>
#include <windows.h>
#include "maze_generator.h"
#include "Game.h"

using namespace std;

// Funkcija dobrodoslice koja uzima broj kolona, redova i predmeta od korisnika
void welcome(int& columns, int& rows, int& item_number) {
	cout << "Dobrodosli u igricu bjeg iz lavirinta u Knososu!" << endl << endl;

	while (true) {
		cout << "Unesite broj kolona: ";
		cin >> columns;
		cout << "Unesite broj redova: ";
		cin >> rows;
		if (rows < 7 || columns < 7) {
			cout << "Dimenzije lavirinta moraju biti barem 7x7!" << endl;
		}
		else {
			break;
		}
	}
	while (true) {
		cout << "Unesite broj predmeta: ";
		cin >> item_number;
		// Broj polja u lavirintu je (columns - 1) * (rows - 1), oduzimam 2 za robota i minotaura, 
		// i oduzimam (columns + rows) * 2 jer je to minilani broj blokoava
		if (item_number > ((columns - 1) * (rows - 1) - 2) - ((columns + rows) * 2)) {
			cout << "Broj predmeta ne moze biti veci od broja slobodnih polja lavirinta!" << endl;
			cout << ((columns - 1) * (rows - 1) - 2) - ((columns + rows) * 2);
		}
		else if (item_number < 4) {
			cout << "Broj predmeta mora biti veci od 3!" << endl;
		}
		else {
			break;
		}
	}
	/*cout << endl << "Igra pocinje za 3!" << endl;
	Sleep(1000);
	cout << "2!" << endl;
	Sleep(1000);
	cout << "1!" << endl;
	Sleep(1000);
	cout << "Sretno!" << endl;
	Sleep(500);*/

	//Brisanje teksta iz terminala
	system("CLS");
	
}

int main(){
	int columns, rows, item_number;

	welcome(columns, rows, item_number);
	
	Game game(columns, rows, item_number);	

	game.start();

}