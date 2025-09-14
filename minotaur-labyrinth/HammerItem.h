/**
 * HammerItem.h
 *
 * Funkcionalnost:
 * - Definise klasu HammerItem koja nasledjuje apstraktnu klasu Item
 * - Predstavlja predmet koji omogucava razbijanje zidova u lavirintu
 * - Implementira efekat predmeta kroz metodu applyEffect
 *
 * Autori: Ognjen
 * Datum poslednje izmjene: Feb 22, 2025
 */
#pragma once
#include "Item.h"

class HammerItem : public Item {
public:
	HammerItem();

	void applyEffect() const;
};

