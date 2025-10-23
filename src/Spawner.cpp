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
    float x = static_cast<float>(std::rand()) / RAND_MAX * mapWidth;
    float y = static_cast<float>(std::rand()) / RAND_MAX * mapHeight;
    return {x, y};
}

bool Spawner::placeItem(Item *item)
{
    const int MAX_ATTEMPTS = 50;

    for (int i = 0; i < MAX_ATTEMPTS; ++i)
    {
        sf::Vector2f pos = getRandomPosition();
        item->setPosition(pos);
        
        sf::FloatRect hb = item->getHitbox();

        std::cout << "Attempt " << i
                  << ": pos(" << pos.x << ", " << pos.y << ") "
                  << "hitbox(pos=" << hb.position.x << "," << hb.position.y
                  << " size=" << hb.size.x << "," << hb.size.y << ")\n";

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
