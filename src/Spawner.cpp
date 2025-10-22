#include "Spawner.h"
#include <iostream>

Spawner::Spawner(const Map &gameMap)
    : map(gameMap),
      mapWidth(gameMap.getWidth()),
      mapHeight(gameMap.getHeight())
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

sf::Vector2f Spawner::getRandomPosition()
{
    // Compute half extents of the map
    float halfWidth = mapWidth / 2.f;
    float halfHeight = mapHeight / 2.f;

    // Generate random coordinates between -half and +half for both axes
    float x = static_cast<float>(std::rand()) / RAND_MAX * mapWidth - halfWidth;
    float y = static_cast<float>(std::rand()) / RAND_MAX * mapHeight - halfHeight;

    return {x, y};
}

bool Spawner::placeItem(Item *item)
{
    const int MAX_ATTEMPTS = 50;

    for (int i = 0; i < MAX_ATTEMPTS; ++i)
    {
        sf::Vector2f pos = getRandomPosition();
        item->setPosition(pos);

        if (!map.isBlocked(item->getHitbox()))
        {
            item->setActive(true);
            item->setVisible(true);
            return true;
        }
    }

    std::cerr << "Failed to place item after " << MAX_ATTEMPTS << " attempts.\n";
    return false;
}

bool Spawner::placeEntity(Entity *entity)
{
    const int MAX_ATTEMPTS = 50;

    for (int i = 0; i < MAX_ATTEMPTS; ++i)
    {
        sf::Vector2f pos = getRandomPosition();
        entity->setPosition(pos);

        if (!map.isBlocked(entity->getHitbox()))
        {
            entity->setActive(true);
            entity->setVisible(true);
            return true;
        }
    }

    std::cerr << "Failed to place entity after " << MAX_ATTEMPTS << " attempts.\n";
    return false;
}
