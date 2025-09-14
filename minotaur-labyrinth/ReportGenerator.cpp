/**
 * ReportGenerator.cpp
 *
 * Implementacija klase ReportGenerator koja omogucava generisanje
 * zavrsnog izvjestaja o trenutnom stanju igre lavirint.
 * Izvjestaj ukljucuje prikaz stanja lavirinta, pozicija ucesnika,
 * broj predmeta i rezultat igre.
 * Izvjestaj se upisuje u tekstualni fajl, a takodje se prikazuje i na konzoli.
 *
 * Autor: Ognjen
 * Datum poslednje izjmene: 14.9.2025.
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
    std::string report = generateReportContent(game);

    std::ofstream reportFile(filename);
    if (!reportFile.is_open()) {
        std::cerr << "Greska: Nije moguce kreirati izvjestaj!" << std::endl;
        return;
    }

    reportFile << report;
    reportFile.close();

    system("CLS");
    std::cout << "Izvjestaj uspesno generisan: " << filename << std::endl;
    std::cout << report;
}

std::string ReportGenerator::generateReportContent(Game& game) {
    std::ostringstream oss;

    oss << "=== KONACNI IZVJESTAJ IGRICE LAVIRINT ===\n\n";

    oss << "=== STANJE LAVIRINTA ===\n";
    oss << getMazeStateString(game) << "\n";

    oss << "=== POZICIJE ===\n";
    oss << getPositionsString(game) << "\n";

    oss << "=== BROJ PREDMETA ===\n";
    oss << getItemsString(game) << "\n";

    oss << "=== REZULTAT IGRE ===\n";
    if (game.getResult()) {
        oss << "Igrac je stigao do izlaza i pobedio!\n";
    }
    else {
        oss << "Igrac nije stigao do izlaza i izgubio je igru.\n";
    }

    return oss.str();
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

    return "Ukupan broj predmeta u lavirintu: " + std::to_string(itemCount) + "\n";
}