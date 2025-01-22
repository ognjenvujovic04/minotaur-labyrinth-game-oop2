#include "ShieldItem.h"
#include <iostream>

using namespace std;

ShieldItem::ShieldItem() : Item(SHIELD, 3) {}

void ShieldItem::applyEffect() const {
	cout << "Stit aktiviran. Sada ste zasticeni od Minotaura.\n";
}
