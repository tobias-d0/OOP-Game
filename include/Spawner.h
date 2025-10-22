#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>

#include "Map.h"
#include "Item.h"
#include "Entity.h"

class Spawner
{
private:
    const Map &map; // Reference to the world map
    float mapWidth;
    float mapHeight;

    // Helper for random position generation
    sf::Vector2f getRandomPosition();

public:
    Spawner(const Map &gameMap);

    // Finds a random valid position on the map for placement
    bool placeItem(Item *item);
    bool placeEntity(Entity *entity);
};
