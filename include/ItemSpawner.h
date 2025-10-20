#pragma once 

#include <cstdlib>
#include <ctime>
#include "Item.h"
#include "Map.h"

class ItemSpawner{
    private:
        int mapHeight;
        int mapWidth;
        std::vector<Item*> spawnedItems;
    public:
        ItemSpawner(const Map& map);
        void spawnItem(Item* item );
};