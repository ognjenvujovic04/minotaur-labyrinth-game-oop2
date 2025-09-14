/**
 * ShieldItem.h
 *
 * Funkcionalnost:
 * - Definise klasu ShieldItem koja nasledjuje apstraktnu klasu Item
 * - Predstavlja predmet koji pruza zastitu robotu (npr. od minotaura)
 * - Implementira efekat predmeta kroz metodu applyEffect
 *
 * Autori: Ognjen
 * Datum poslednje izjmene: Feb 22, 2025
 */
#pragma once
#include "Item.h"

class ShieldItem : public Item {
public:
	ShieldItem();

	void applyEffect() const;
};

