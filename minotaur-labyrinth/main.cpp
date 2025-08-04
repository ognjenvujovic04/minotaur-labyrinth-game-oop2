/**
 * Glavni modul za projekat minotaur-labyrinth
 *
 * Funkcionalnost:
 * - Omogucava unos parametara lavirinta (broj kolona, redova i predmeta)
 * - Validira unose kako iz komandne linije tako i interaktivne unose
 * - Pokrece glavnu igru sa zadatim parametrima
 *
 * Autori:
 * - [Ime i prezime autora 1]
 * - [Ime i prezime autora 2] (ako postoji)
 *
 * Poslednja izmena:
 * Datum: [DD.MM.YYYY]
 * Autor: [Ime autora koji je izvrsio poslednju izmenu]
 */

#include <iostream>
#include <windows.h>
#include <regex>
#include "Game.h"

using namespace std;

/**
 * Brise greske unosa iz ulaznog toka
 *
 * Funkcionalnost:
 * - Resetuje stanje ulaznog toka
 * - Ignorise preostale karaktere u ulaznom toku do kraja linije
 */
void clearInputError() {
    cin.clear();
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

/**
 * Provjerava da li string sadrzi samo cifre
 *
 * @param str String koji se proverava
 * @return bool - true ako su svi karakteri cifre, false inace
 */
bool isDigitsOnly(const std::string& str) {
    static const regex digits_only("^[0-9]+$");
    return regex_match(str, digits_only);
}

/**
 * Funkcija dobrodoslice koja prikazuje pocetni meni i omogucava unos parametara igre
 *
 * @param columns Referenca na broj kolona lavirinta
 * @param rows Referenca na broj redova lavirinta
 * @param item_number Referenca na broj predmeta u lavirintu
 *
 * Funkcionalnost:
 * - Interaktivno prikuplja podatke od korisnika
 * - Validira unose i obezbedjuje ponovni unos u slucaju greske
 * - Brise ekran nakon uspesnog unosa
 *
 * Uslovi:
 * - Minimalne dimenzije lavirinta su 16x16
 * - Broj predmeta mora biti veci od 3
 * - Broj predmeta ne sme premasiti broj slobodnih polja
 */
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
        if (rows < 16 || columns < 16) {
            cout << "Dimenzije lavirinta moraju biti barem 16x16!" << endl;
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

    system("CLS");
}

/**
 * Validira unijete parametre za igru
 *
 * @param columns Broj kolona lavirinta
 * @param rows Broj redova lavirinta
 * @param item_number Broj predmeta u lavirintu
 * @return bool - true ako su parametri validni, false inace
 *
 * Uslovi:
 * - Minimalne dimenzije lavirinta su 16x16
 * - Broj predmeta mora biti veci od 3
 * - Broj predmeta ne sme premasiti broj slobodnih polja
 */
bool validateInputs(int columns, int rows, int item_number) {
    if (columns < 16 || rows < 16) {
        cerr << "Dimenzije lavirinta moraju biti barem 16x16!" << endl;
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

/**
 * Glavna funkcija programa
 *
 * @param argc Broj argumenata komandne linije
 * @param argv Niz argumenata komandne linije
 * @return int - Statusni kod izlaska (0 za uspeh, 1 za gresku)
 *
 * Funkcionalnost:
 * - Obradjuje argumente komandne linije (ako postoje)
 * - U suprotnom, pokrece interaktivni meni
 * - Validira unose i pokrece igru sa zadatim parametrima
 *
 * Tipovi izuzetaka:
 * - invalid_argument - ako argumenti nisu celi brojevi
 * - out_of_range - ako su brojevi van dozvoljenog opsega
 */
int main(int argc, char* argv[]) {
    int columns, rows, item_number;

    if (argc == 4) {
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