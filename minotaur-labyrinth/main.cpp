#include <iostream>
#include <windows.h>
#include "maze_generator.h"
#include "Game.h"

using namespace std;


// Funkcija za brisanje greske unosa
void clearInputError() {
	cin.clear();
	cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

// Funkcija dobrodoslice koja uzima broj kolona, redova i predmeta od korisnika
void welcome(int& columns, int& rows, int& item_number) {
	cout << "Dobrodosli u igricu bjeg iz lavirinta u Knososu!" << endl << endl;

	while (true) {
		cout << "Unesite broj kolona: ";
		if (!(cin >> columns)) {
			cout << "Pogresan unos! Molimo vas unesite prirodan broj." << endl;
			clearInputError();
			continue;
		}
		cout << "Unesite broj redova: ";
		if (!(cin >> rows)) {
			cout << "Pogresan unos! Molimo vas unesite prirodan broj." << endl;
			clearInputError();
			cin.clear();
			continue;
		}
		if (rows < 15 || columns < 15) {
			cout << "Dimenzije lavirinta moraju biti barem 15x15!" << endl;
			continue;
		}
		break;
		
	}

	while (true) {
		cout << "\nUnesite broj predmeta: ";
		if (!(cin >> item_number)) {
			cout << "Pogresan unos! Molimo vas unesite prirodan broj." << endl;
			clearInputError();
			continue;
		}
		// Broj polja u lavirintu je (columns - 1) * (rows - 1), oduzimam 2 za robota i minotaura, 
		// i oduzimam (columns + rows) * 2 jer je to minimalan broj blokoava
		if (item_number > ((columns - 1) * (rows - 1) - 2) - ((columns + rows) * 2)) {
			cout << "Broj predmeta ne moze biti veci od broja slobodnih polja lavirinta!" << endl;
			cout << "Broj slobodnih polja:" << ((columns - 1) * (rows - 1) - 2) - ((columns + rows) * 2);
			continue;
		}
		else if (item_number < 4) {
			cout << "Broj predmeta mora biti veci od 3!" << endl;
			continue;
		}
		break;
		
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