#pragma once
#include "Item.h"

class ShieldItem : public Item {
public:
	ShieldItem();
	~ShieldItem();

	void applyEffect() const;
	void resetEffect() const;
};

