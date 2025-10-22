#pragma once
#include "Item.h"

class Torch : public Item {
public:
    Torch();

    void useItem() override {
        // e.g. toggle light, restore warmth, etc.
    }
};
