/**
 * FogItem.h
 *
 * Funkcionalnost:
 * - Definise klasu FogItem koja nasledjuje apstraktnu klasu Item
 * - Predstavlja predmet koji aktivira efekat magle (sakriva delove lavirinta)
 * - Implementira efekat predmeta kroz metodu applyEffect
 *
 * Autori: Ognjen
 * Datum poslednje izjmene: Feb 22, 2025
 */
#pragma once
#include "Item.h"

class FogItem : public Item{
public:
	FogItem();

	void applyEffect() const;
};

