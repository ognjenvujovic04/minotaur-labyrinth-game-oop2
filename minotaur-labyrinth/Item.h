#pragma once

enum ItemType { FOG, SWORD, SHIELD, HAMMER };

class Item {
protected:
    ItemType type;  // Tip predmeta
    int duration;   // Trajanje efekta u potezima

public:
    Item(ItemType type, int duration);

    // Dohvatanje tipa predmeta
    ItemType getType() const;

    // Dohvatanje trajanja efekta
    int getDuration() const;

	void decreaseDuration();   

    // Efekat predmeta (apstraktna metoda)
    virtual void applyEffect() const = 0;
};

