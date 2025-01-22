#include "ShieldItem.h"
#include <iostream>

using namespace std;

ShieldItem::ShieldItem() : Item(SHIELD, 3) {}

void ShieldItem::applyEffect() const {
    cout << "Magla rata aktivirana! Vidljivost smanjena na 3x3 podrucje.\n";
}

void ShieldItem::resetEffect() const {
    cout << "Magla rata uklonjena. Vidljivost normalna.\n";
}
