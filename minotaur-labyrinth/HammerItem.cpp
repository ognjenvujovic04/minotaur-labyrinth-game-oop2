#include "HammerItem.h"
#include <iostream>

using namespace std;

HammerItem::HammerItem() : Item(HAMMER, 3) {}

void HammerItem::applyEffect() const {
	cout << "Cekic aktiviran! Ovim predmetom mozete unistiti zidove.\n";
}

