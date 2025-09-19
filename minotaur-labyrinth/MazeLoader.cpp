/**
 * MazeLoader.cpp
 *
 * Funkcionalnost:
 * - Implementacija klase za ucitavanje lavirinta iz tekstualnog dokumenta.
 * - Parsiranje karaktera i postavljanje pozicija robota, minotaura i predmeta.
 * - Jednostavno ucitavanje bez testiranja.
 *
 * Autori: Ognjen
 * Datum poslednje izmene: 19.9.2025.
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <windows.h>
#include "MazeLoader.h"

using namespace std;

/**
 * loadMaze
 *
 * Funkcionalnost:
 * - Ucitava lavirint iz tekstualnog fajla.
 * - Postavlja pozicije robota, minotaura i predmeta na osnovu karaktera u fajlu.
 * - Ne vrsi testiranje putanje - samo ucitava mapu za dalju upotrebu.
 *
 * Ulazni argumenti:
 * - Maze& mazeClass: referenca na objekat klase Maze koji se popunjava.
 * - string filename: ime fajla iz kojeg se ucitava lavirint.
 *
 * Povratna vrednost:
 * - bool: true ako je uspesno ucitan lavirint, false inace.
 */
bool MazeLoader::loadMaze(Maze& mazeClass, string filename) {
	// Otvaranje fajla
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Greska: Ne mogu da otvorim fajl " << filename << endl;
        return false;
    }

    // Ucitavanje sadrzaja fajla u vektor stringova
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        // Ako red pocinje sa '*' pocinje komentar
        if (!line.empty() && line[0] == '*') {
            break;
        }
        lines.push_back(line);
    }
    file.close();

    if (lines.empty()) {
        cout << "Greska: Fajl je prazan!" << endl;
        return false;
    }

    // Postavljanje dimenzija lavirinta
    mazeClass.rows = static_cast<int>(lines.size());
    mazeClass.columns = static_cast<int>(lines[0].length());

    // Alokacija memorije za matricu lavirinta
    mazeClass.mazeMatrix = new char* [mazeClass.rows];
    for (int i = 0; i < mazeClass.rows; i++) {
        mazeClass.mazeMatrix[i] = new char[mazeClass.columns];
    }

    // Ucitavanje sadrzaja i pronalazenje pozicija
    bool robotFound = false, minotaurFound = false;

    for (int i = 0; i < mazeClass.rows; i++) {
        for (int j = 0; j < mazeClass.columns; j++) {
            if (j < static_cast<int>(lines[i].length())) {
                mazeClass.mazeMatrix[i][j] = lines[i][j];

                if (lines[i][j] == 'R') {
                    mazeClass.robotPosition = make_tuple(i, j);
                    robotFound = true;
                }

                if (lines[i][j] == 'M') {
                    mazeClass.minotaurPosition = make_tuple(i, j);
                    minotaurFound = true;
                }
            }
            else {
                mazeClass.mazeMatrix[i][j] = '#';
            }
        }
    }

    if (!robotFound) {
        cout << "Upozorenje: Robot (R) nije pronadjen u lavirintu!" << endl;
        // Postavljanje default pozicije
        mazeClass.robotPosition = make_tuple(1, 1);
    }

    if (!minotaurFound) {
        cout << "Upozorenje: Minotaur (M) nije pronadjen u lavirintu!" << endl;
        // Postavljanje default pozicije
        mazeClass.minotaurPosition = make_tuple(mazeClass.rows - 2, mazeClass.columns - 2);
    }

    // Ispis ucitanog lavirinta
    cout << "Lavirint je uspesno ucitan iz fajla: " << filename << endl;
    for (int i = 0; i < mazeClass.rows; i++) {
        for (int j = 0; j < mazeClass.columns; j++) {
			cout << mazeClass.mazeMatrix[i][j];
        }
        cout << endl;
    }
    cout << endl;

    // Ispis pozicija
    cout << "Robot pozicija: (" << get<0>(mazeClass.robotPosition)
        << ", " << get<1>(mazeClass.robotPosition) << ")" << endl;
    cout << "Minotaur pozicija: (" << get<0>(mazeClass.minotaurPosition)
        << ", " << get<1>(mazeClass.minotaurPosition) << ")" << endl;

    Sleep(3000);

    return true;
}