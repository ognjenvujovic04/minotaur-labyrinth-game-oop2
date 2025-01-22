#pragma once
#include "Item.h"

class FogItem : public Item{
public:
	FogItem();
	~FogItem();

	void applyEffect() const;
	void resetEffect() const;
};

