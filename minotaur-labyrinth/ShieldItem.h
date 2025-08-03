#pragma once
#include "Item.h"

class ShieldItem : public Item {
public:
	ShieldItem();

	void applyEffect() const;
};

