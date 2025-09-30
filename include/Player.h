#pragma once

#include "Entity.h"
#include "Inventory.h"

class Player : public Entity {
 private:
  int hunger;
  int warmth;
  Inventory inventory;

 public:
  void pickUpItem();
  void useItem();
  void craftItem();

  int get_hunger();
  void set_hunger(int hunger);
  int get_warmth();
  void set_warmth(int warmth);
};