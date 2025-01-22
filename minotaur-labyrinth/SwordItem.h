#pragma once
#include "Item.h"

class SwordItem : public Item {
public:
	SwordItem();
	~SwordItem();

	void applyEffect() const;
	void resetEffect() const;
};

