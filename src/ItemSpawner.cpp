#include "ItemSpawner.h"
#include <iostream>

ItemSpawner::ItemSpawner(const Map& gameMap)
    : map(gameMap), mapWidth(gameMap.getWidth()), mapHeight(gameMap.getHeight()) {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // random seed
}

void ItemSpawner::spawnItem(Item* item) {
    const int MAX_ATTEMPTS = 50;
    int attempts = 0;
    bool placed = false;

    while (!placed && attempts < MAX_ATTEMPTS) {
        float x = static_cast<float>(std::rand() % static_cast<int>(mapWidth));
        float y = static_cast<float>(std::rand() % static_cast<int>(mapHeight));

        if (!map.isBlocked(item->getHitbox())) {
            item->setPosition({x, y});
            activeItems.push_back(item);
            placed = true;
        }

        attempts++;
    }

    if (!placed) {
        std::cerr << "Failed to spawn item after " << MAX_ATTEMPTS << " attempts.\n";
    }
}

void ItemSpawner::clearItems() {
    activeItems.clear();
}

const std::vector<Item*>& ItemSpawner::getActiveItems() const {
    return activeItems;
}