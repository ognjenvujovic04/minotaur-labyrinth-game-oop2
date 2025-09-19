/**
 * ReportGenerator.h
 *
 * Omogucava generisanje izvjestaja o trenutnom stanju igre.
 * U izvjestaju se nalaze podaci o lavirintu, pozicijama igraca i predmeta.
 * Izvjestaj se cuva u tekstualni fajl ciji se naziv moze proslediti.
 *
 * Autor: Ognjen
 * Datum poslednje izmjene: 14.9.2025.
 */
#pragma once
#include "Game.h"
#include <string>
#include <fstream>
#include <ctime>

class ReportGenerator {
public:
    static void generateReport( Game& game, const std::string& filename = "../assets/reports/maze_report.txt");

private:
    static std::string generateReportContent(Game& game);
    static std::string getMazeStateString( Game& game);
    static std::string getPositionsString(Game& game);
    static std::string getItemsString(Game& game);
};