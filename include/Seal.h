#pragma once
#include "Enemy.h"

class Seal : public Enemy {
public:
    Seal(Player* playerPtr);

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    void takeDamage(int amount) override;
private:
    float speed = 60.f;
    float fleeRange = 250.f; // start fleeing if closer than this
};
