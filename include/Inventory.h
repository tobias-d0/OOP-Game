#pragma once

#include <string>
#include "Item.h"

class Inventory {
 private:
  Item** items;
  const int MAX_SIZE = 10;
  int currentSize;

 public:
  Inventory();

  void addItem(Item* item);
  bool hasItem(std::string name);

  void removeItem(Item* item);
  void removeItem(int index);
  void removeItem(std::string itemName);

  bool isFull();
  int getSize();
  void displayInventory();

  ~Inventory();
};