/**
 * ReportGenerator.h
 *
 * Omogucava generisanje izvestaja o trenutnom stanju igre.
 * U izvestaju se nalaze podaci o lavirintu, pozicijama igraca i predmeta.
 * Izvestaj se cuva u tekstualni fajl ciji se naziv moze proslediti.
 *
 * Autor: Ognjen
 * Datum poslednje izmene: avgust 2025
 */
#pragma once
#include "Game.h"
#include <string>
#include <fstream>
#include <ctime>

class ReportGenerator {
public:
    static void generateReport( Game& game, const std::string& filename = "maze_report.txt");

private:
    static std::string getMazeStateString( Game& game);
    static std::string getPositionsString(Game& game);
    static std::string getItemsString(Game& game);
};