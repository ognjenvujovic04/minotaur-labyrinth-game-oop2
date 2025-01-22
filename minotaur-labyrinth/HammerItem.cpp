#include "HammerItem.h"
#include <iostream>

using namespace std;

HammerItem::HammerItem() : Item(HAMMER, 3) {}

void HammerItem::applyEffect() const {
    cout << "Magla rata aktivirana! Vidljivost smanjena na 3x3 podrucje.\n";
}

void HammerItem::resetEffect() const {
    cout << "Magla rata uklonjena. Vidljivost normalna.\n";
}
