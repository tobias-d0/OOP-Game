#pragma once

#include <string>
#include "Item.h"

class Inventory {
 private:
  Item** items; //dynamic array of pointers to item objects
  const int MAX_SIZE = 10; //max number of items in inventory
  int currentSize; //current size of inventory

 public:
  Inventory(); //default constructor 

  void addItem(Item* item); // Add an item to the inventory
  bool hasItem(std::string name); // Check if inventory contains an item by name
  bool hasItem(int index); // Check if inventory contains an item index

  void removeItem(Item* item); // Remove an item by pointer
  void removeItem(int index); // Remove an item by index
  void removeItem(std::string itemName); // Remove an item by its name

  bool isFull(); //check if full
  int getSize(); //check inventory size 
  Item* getItem(int index); // Get a pointer to an item at a specific index
  void displayInventory(); //display inventory

  ~Inventory(); //destructor
};