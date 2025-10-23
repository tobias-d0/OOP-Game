#pragma once
#include "Item.h"

class Radio : public Item {
public:
    Radio();

    void useItem() override {
        // e.g. toggle light, restore warmth, etc.
    }
};
