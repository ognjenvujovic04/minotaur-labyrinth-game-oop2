#include "Item.h"

Item::Item(ItemType type, int duration) : type(type), duration(duration) {}

ItemType Item::getType() const {
    return type;
}

int Item::getDuration() const {
    return duration;
}