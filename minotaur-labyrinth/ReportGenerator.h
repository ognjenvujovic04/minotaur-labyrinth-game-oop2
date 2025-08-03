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