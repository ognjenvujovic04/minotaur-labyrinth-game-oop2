#include "SwordItem.h"
#include <iostream>

using namespace std;

SwordItem::SwordItem() : Item(SWORD, 3) {}

void SwordItem::applyEffect() const {
	cout << "Mac aktiviran! Ovim predmetom mozete unistiti Minotaura.\n";
}

