#pragma once
#include <vector>
#include <memory>
#include <cstdlib>
#include <ctime>
#include "Item.h"
#include "Map.h"

class ItemSpawner {
private:
    const Map& map;  // Reference to the game map
    std::vector<Item*> activeItems;

    float mapWidth;
    float mapHeight;

public:
    ItemSpawner(const Map& gameMap);

    void spawnItem(Item* item);
    void render(sf::RenderWindow& window);
    void clearItems();

    std::vector<Item*>& getActiveItems();
};
