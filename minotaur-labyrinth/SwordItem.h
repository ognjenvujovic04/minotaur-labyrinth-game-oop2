#pragma once
#include "Item.h"

class SwordItem : public Item {
public:
	SwordItem();

	void applyEffect() const;
};

