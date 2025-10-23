#pragma once
#include "Item.h"

class Electronics : public Item {
public:
    Electronics();

    void useItem() override {
        // e.g. toggle light, restore warmth, etc.
    }
};
