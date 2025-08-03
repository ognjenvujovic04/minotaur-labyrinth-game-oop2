#include "ReportGenerator.h"
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

void ReportGenerator::generateReport( Game& game, const std::string& filename) {
    std::ofstream reportFile(filename);

    if (!reportFile.is_open()) {
        cerr << "Error: Could not create report file!" << std::endl;
        return;
    }

    reportFile << "=== MAZE GAME FINAL REPORT ===\n\n";

    reportFile << "=== MAZE STATE ===\n";
    reportFile << getMazeStateString(game) << "\n";

    reportFile << "=== POSITIONS ===\n";
    reportFile << getPositionsString(game) << "\n";

    reportFile << "=== ITEMS COUNT ===\n";
    reportFile << getItemsString(game) << "\n";

    reportFile << "=== GAME RESULT ===\n";
    if (game.getResult()) {
        reportFile << "Player reached the exit and won the game!\n";
    } else {
		reportFile << "Player did not reach the exit and lost the game.\n";
    }

    reportFile.close();
    system("CLS");
	//print the report to console
    cout << "Report generated successfully: " << filename << endl;
    cout << "=== MAZE GAME FINAL REPORT ===\n\n";
    cout << "=== MAZE STATE ===\n";
    cout << getMazeStateString(game) << "\n";
    cout << "=== POSITIONS ===\n";
    cout << getPositionsString(game) << "\n";
    cout << "=== ITEMS COUNT ===\n";
    cout << getItemsString(game) << "\n";
    cout << "=== GAME RESULT ===\n";
    if (game.getResult()) {
        cout << "Player reached the exit and won the game!\n";
    } else {
        cout << "Player did not reach the exit and lost the game.\n";
	}
}

std::string ReportGenerator::getMazeStateString(Game& game) {
    return game.getMazeString();
}

std::string ReportGenerator::getPositionsString(Game& game) {
    tuple<int,int> robotPos = game.getRobotPosition();
    tuple<int, int> minotaurPos = game.getMinotaurPosition();

	string result;

	result += "Robot Position: (" + std::to_string(get<0>(robotPos)) + ", " + std::to_string(get<1>(robotPos)) + ")\n";
	result += "Minotaur Position: (" + std::to_string(get<0>(minotaurPos)) + ", " + std::to_string(get<1>(minotaurPos)) + ")\n";

    return result;
}

std::string ReportGenerator::getItemsString(Game& game) {
	int itemCount = game.getItemNumber();

    return "Total items in maze: " + std::to_string(itemCount) + "\n";
}