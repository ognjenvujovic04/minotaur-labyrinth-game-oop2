#include "FogItem.h"
#include <iostream>

using namespace std;

FogItem::FogItem() : Item(FOG, 3) {}

void FogItem::applyEffect() const {
    cout << "Magla rata aktivirana! Vidljivost smanjena na 3x3 podrucje.\n";
}

void FogItem::resetEffect() const {
    cout << "Magla rata uklonjena. Vidljivost normalna.\n";
}
