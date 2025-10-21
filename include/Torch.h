#pragma once
#include "Item.h"

class Torch : public Item
{
public:
  Torch()
      : Item("Torch", "assets/textures/Torch.png") {}

  void useItem() override {
    // doesn't do anything in this instance
  }
};
