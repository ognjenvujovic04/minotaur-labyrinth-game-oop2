#include <iostream>
#include <windows.h>
#include <regex>
#include "maze_generator.h"
#include "Game.h"

using namespace std;

// Funkcija za brisanje greske unosa
void clearInputError() {
    cin.clear();
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

// Proverava da li je string sastavljen samo od cifara
bool isDigitsOnly(const std::string& str) {
    static const regex digits_only("^[0-9]+$");
    return regex_match(str, digits_only);
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

	//Brisanje teksta iz terminala
    system("CLS");
}

// Proverava da li su uneti argumenti validni brojevi i da li su u opsegu
bool validateInputs(int columns, int rows, int item_number) {
    if (columns < 15 || rows < 15) {
        cerr << "Dimenzije lavirinta moraju biti barem 15x15!" << endl;
        return false;
    }
    int max_items = ((columns - 1) * (rows - 1) - 2) - ((columns + rows) * 2);
    if (item_number > max_items) {
        cerr << "Broj predmeta ne moze biti veci od broja slobodnih polja lavirinta!" << endl;
        return false;
    }
    if (item_number < 4) {
        cerr << "Broj predmeta mora biti veci od 3!" << endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    int columns, rows, item_number;

    if (argc == 4) {
		// Proveravam da li su uneti argumenti validni brojevi
        if (!isDigitsOnly(argv[1]) || !isDigitsOnly(argv[2]) || !isDigitsOnly(argv[3])) {
            cerr << "Svi argumenti moraju biti cijeli brojevi. Izlazak iz programa..." << endl;
            return 1;
		}

        try {
            columns = std::stoi(argv[1]);
            rows = std::stoi(argv[2]);
            item_number = std::stoi(argv[3]);

            if (!validateInputs(columns, rows, item_number)) {
                cout << "Unos iz komandne linije nije validan. Izlazak iz programa..." << endl;
                return 1;
            }
        }
        catch (const std::invalid_argument&) {
            cerr << "Svi argumenti moraju biti celi brojevi. Izlazak iz programa..." << endl;
            return 1;
        }
        catch (const std::out_of_range&) {
            cerr << "Uneti brojevi su van dozvoljenog opsega. Izlazak iz programa..." << endl;
            return 1;
        }
    }
    else if (argc == 1) {
        welcome(columns, rows, item_number);
    }
    else {
        cerr << "Nedovoljan broj argumenata. Izlazak iz programa..." << endl;
        return 1;
    }

    Game game(columns, rows, item_number);
    game.start();
    return 0;
}
