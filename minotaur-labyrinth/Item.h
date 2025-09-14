/**
 * Item.h
 *
 * Funkcionalnost:
 * - Definise apstraktnu osnovnu klasu za sve predmete u igri
 * - Predmeti imaju tip i trajanje efekta koji se smanjuje svakim potezom
 * - Klasa sadrzi virtuelnu metodu applyEffect koju implementiraju konkretni tipovi predmeta
 * - Ova klasa se nasledjuje od strane klasa FogItem, SwordItem, ShieldItem, HammerItem
 *
 * Autori: Ognjen 
 * Datum poslednje izmjene: Feb 22, 2025
 */
#pragma once

enum ItemType { FOG, SWORD, SHIELD, HAMMER };

class Item {
protected:
    ItemType type;  // Tip predmeta
    int duration;   // Trajanje efekta u potezima

public:
    Item(ItemType type, int duration);

    ItemType getType() const;
    int getDuration() const;

    void decreaseDuration();
    virtual void applyEffect() const = 0;
};

