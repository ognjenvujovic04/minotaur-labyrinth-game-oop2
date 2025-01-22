#pragma once
#include "Item.h"

class HammerItem : public Item {
public:
	HammerItem();
	~HammerItem();

	void applyEffect() const;
	void resetEffect() const;
};

