/**
 * ReportGenerator.cpp
 *
 * Implementacija klase ReportGenerator koja omogucava generisanje
 * zavrsnog izvestaja o trenutnom stanju igre lavirint.
 * Izveštaj ukljucuje prikaz stanja lavirinta, pozicija ucesnika,
 * broj predmeta i rezultat igre.
 * Izvestaj se upisuje u tekstualni fajl, a takodje se prikazuje i na konzoli.
 *
 * Autor: Ognjen
 * Datum poslednje izmene: avgust 2025
 */
#include "ReportGenerator.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

/**
 * Generise zavrsni izvjestaj igre u tekstualnom fajlu i prikazuje ga na konzoli.
 *
 * @param game Referenca na objekat igre od kojeg se preuzimaju podaci.
 * @param filename Ime fajla u koji se upisuje izvjestaj.
 */
void ReportGenerator::generateReport(Game& game, const std::string& filename) {
    std::ofstream reportFile(filename);

    if (!reportFile.is_open()) {
        cerr << "Greska: Nije moguce kreirati izvestaj!" << std::endl;
        return;
    }

    reportFile << "=== KONACNI IZVESTAJ IGRICE===\n\n";

    reportFile << "=== STANJE LAVIRINTA ===\n";
    reportFile << getMazeStateString(game) << "\n";

    reportFile << "=== POZICIJE ===\n";
    reportFile << getPositionsString(game) << "\n";

    reportFile << "=== BROJ PREDMETA ===\n";
    reportFile << getItemsString(game) << "\n";

    reportFile << "=== REZULTAT IGRE ===\n";
    if (game.getResult()) {
        reportFile << "Igrac je stigao do izlaza i pobedio!\n";
    }
    else {
        reportFile << "Igrac nije stigao do izlaza i izgubio je igru.\n";
    }

    reportFile.close();
    system("CLS");
    // Ispis na konzolu
    cout << "Izvestaj uspesno generisan: " << filename << endl;
    cout << "\n=== KONACNI IZVESTAJ IGRICE LAVIRINT ===\n\n";
    cout << "=== STANJE LAVIRINTA ===\n";
    cout << getMazeStateString(game) << "\n";
    cout << "=== POZICIJE ===\n";
    cout << getPositionsString(game) << "\n";
    cout << "=== BROJ PREDMETA ===\n";
    cout << getItemsString(game) << "\n";
    cout << "=== REZULTAT IGRE ===\n";
    if (game.getResult()) {
        cout << "Igrac je stigao do izlaza i pobedio!\n";
    }
    else {
        cout << "Igrac nije stigao do izlaza i izgubio je igru.\n";
    }
}

/**
 * Dohvata string koji opisuje trenutno stanje lavirinta iz igre.
 *
 * @param game Referenca na objekat igre.
 * @return String sa opisom lavirinta.
 */
std::string ReportGenerator::getMazeStateString(Game& game) {
    return game.getMazeString();
}

/**
 * Dohvata string sa informacijama o pozicijama robota i minotaura.
 * Ukoliko je neki od njih ubijen, to se jasno navodi.
 *
 * @param game Referenca na objekat igre.
 * @return String sa informacijama o pozicijama ucesnika.
 */
std::string ReportGenerator::getPositionsString(Game& game) {
    tuple<int, int> robotPos = game.getRobotPosition();
    tuple<int, int> minotaurPos = game.getMinotaurPosition();

    string result;
    if (get<0>(robotPos) == -1 && get<1>(robotPos) == -1) {
        result += "Robot je ubijen.\n";
    }
    else {
        result += "Pozicija robota: (" + std::to_string(get<0>(robotPos)) + ", " + std::to_string(get<1>(robotPos)) + ")\n";
    }
    if (get<0>(minotaurPos) == -1 && get<1>(minotaurPos) == -1) {
        result += "Minotaur je ubijen.\n";
    }
    else {
        result += "Pozicija minotaura: (" + std::to_string(get<0>(minotaurPos)) + ", " + std::to_string(get<1>(minotaurPos)) + ")\n";
    }
    return result;
}

/**
 * Dohvata string sa informacijom o ukupnom broju predmeta u lavirintu.
 *
 * @param game Referenca na objekat igre.
 * @return String sa brojem predmeta.
 */
std::string ReportGenerator::getItemsString(Game& game) {
    int itemCount = game.getItemNumber();

    return "Ukupan broj predmeta u labirintu: " + std::to_string(itemCount) + "\n";
}