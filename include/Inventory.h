#pragma once

#include <string>
#include <vector>
#include "Item.h"

class Inventory {
 private:
  std::vector<Item*> items;

 public:
  void addItem(Item* item);
  bool hasItem(std::string name);
  void removeItem(Item* item);
  void removeItem(int index);
  void removeItem(std::string itemName);
};