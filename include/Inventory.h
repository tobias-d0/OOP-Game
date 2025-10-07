#pragma once

#include <string>
#include "Item.h"

class Inventory {
 private:
  Item** items;

 public:
  void addItem(Item* item);
  void removeItem(Item* item);
  void removeItem(int index);
  void removeItem(std::string itemName);
};