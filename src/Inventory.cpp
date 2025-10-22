#include "Inventory.h"
#include <iostream>

Inventory::Inventory()
{
    items = new Item *[MAX_SIZE];
    currentSize = 0;

    // Initialize all pointers to nullptr
    for (int i = 0; i < MAX_SIZE; i++)
    {
        items[i] = nullptr;
    }
}

void Inventory::addItem(Item *item)
{
    if (isFull())
    {
        std::cout << "Inventory is full! Item cannot be picked up " << item->getName() << std::endl;
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

bool Inventory::hasItem(std::string name)
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

bool Inventory::hasItem(int index)
{
    return (index >= 0 && index < MAX_SIZE && items[index] != nullptr);
}

void Inventory::removeItem(Item *item)
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

void Inventory::removeItem(int index)
{ // removing item by item in inventory place
    if (index >= 0 && index < MAX_SIZE && items[index] != nullptr)
    {
        std::cout << "Removed " << items[index]->getName() << " from inventory" << std::endl;
        items[index] = nullptr;
        currentSize--;
    }
}

void Inventory::removeItem(std::string itemName)
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

bool Inventory::isFull()
{
    return currentSize >= MAX_SIZE;
}

int Inventory::getSize()
{
    return currentSize;
}

void Inventory::displayInventory()
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

Item *Inventory::getItem(int index)
{
    if (hasItem(index))
    {
        return items[index];
    }
    return nullptr;
}

Inventory::~Inventory()
{

    delete[] items;
}