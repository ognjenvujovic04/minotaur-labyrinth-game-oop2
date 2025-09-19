/**
 * MazeLoader.h
 *
 * Funkcionalnost:
 * - Deklaracija klase za ucitavanje lavirinta iz tekstualnog dokumenta.
 * - Parsiranje karaktera i postavljanje pozicija robota, minotaura i predmeta.
 * - Jednostavno ucitavanje bez testiranja.
 *
 * Autori: Ognjen
 * Datum poslednje izmene: 19.9.2025.
 */

#pragma once


#include <string>
#include <tuple>
#include "Maze.h"

using namespace std;

class MazeLoader {
public:
    static bool loadMaze(Maze& mazeClass, string filename);
};
