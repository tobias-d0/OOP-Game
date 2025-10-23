#include "Inventory.h"
#include <iostream>

Inventory::Inventory()
{
    items = new Item *[MAX_SIZE]; //dynamically allocate array of item ptrs 
    currentSize = 0; //count current size

    // Initialize all pointers to nullptr
    for (int i = 0; i < MAX_SIZE; i++)
    {
        items[i] = nullptr; //no items initialially
    }
}

void Inventory::addItem(Item *item) //function to add item to inventory
{
    if (isFull()) //check if full
    {
        std::cout << "Inventory is full! Item cannot be picked up " << item->getName() << std::endl; //if full print out
        return;
    }

    // Find first free slot in inventory
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (items[i] == nullptr)
        {
            items[i] = item;
            currentSize++;
            std::cout << item->getName() << " has been added to your inventory" << std::endl;
            return;
        }
    }
}

bool Inventory::hasItem(std::string name) //check if item exists by name
{
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (items[i] != nullptr && items[i]->getName() == name)
        {
            return true;
        }
    }
    return false;
}

bool Inventory::hasItem(int index) //check if item exists by index in inventory
{
    return (index >= 0 && index < MAX_SIZE && items[index] != nullptr);
}

void Inventory::removeItem(Item *item) //remove item type
{ // logic for removing item type
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (items[i] == item)
        {
            items[i] = nullptr;
            currentSize--;
            std::cout << "Removed item from inventory" << std::endl;
            return;
        }
    }
}

void Inventory::removeItem(int index) //remove item by index
{ // removing item by item in inventory place
    if (index >= 0 && index < MAX_SIZE && items[index] != nullptr)
    {
        std::cout << "Removed " << items[index]->getName() << " from inventory" << std::endl;
        items[index] = nullptr;
        currentSize--;
    }
}

void Inventory::removeItem(std::string itemName) //remove item by name
{ // remove item by item name
    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (items[i] != nullptr && items[i]->getName() == itemName)
        {
            std::cout << "Removed " << itemName << " from inventory" << std::endl;
            items[i] = nullptr;
            currentSize--;
            return;
        }
    }
    std::cout << "Item " << itemName << " not found in inventory" << std::endl;
}

bool Inventory::isFull() //check if full
{
    return currentSize >= MAX_SIZE;
}

int Inventory::getSize() //check inventory size
{
    return currentSize;
}

void Inventory::displayInventory() //display inventory
{
    std::cout << "___ INVENTORY ___ (" << currentSize << "/" << MAX_SIZE << ")" << std::endl;
    bool empty = true;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (items[i] != nullptr)
        {
            std::cout << i << ". " << items[i]->getName() << std::endl;
            empty = false;
        }
    }

    if (empty)
    {
        std::cout << "Inventory is empty" << std::endl;
    }
    std::cout << "_________________" << std::endl;
}

Item *Inventory::getItem(int index) //get item by index in inventory
{
    if (hasItem(index))
    {
        return items[index];
    }
    return nullptr;
}

Inventory::~Inventory() //destructor
{

    delete[] items;
}