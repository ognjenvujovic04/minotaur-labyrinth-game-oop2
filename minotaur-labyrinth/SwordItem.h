/**
 * SwordItem.h
 *
 * Funkcionalnost:
 * - Definise klasu SwordItem koja nasledjuje apstraktnu klasu Item
 * - Predstavlja predmet koji omogucava robotu da unisti minotaura
 * - Implementira efekat predmeta kroz metodu applyEffect
 *
 * Autori: Ognjen
 * Datum poslednje izmene: avgust 2025
 */
#pragma once
#include "Item.h"

class SwordItem : public Item {
public:
	SwordItem();

	void applyEffect() const;
};

