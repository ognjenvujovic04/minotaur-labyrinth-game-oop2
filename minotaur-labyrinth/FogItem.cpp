#include "FogItem.h"
#include <iostream>

using namespace std;

FogItem::FogItem() : Item(FOG, 3) {}

void FogItem::applyEffect() const {
    cout << "Magla rata aktivna! Vidljivost smanjena na 3x3 podrucje.\n";
}
