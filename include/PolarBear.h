#pragma once
#include "Enemy.h"

class PolarBear : public Enemy {
public:
    PolarBear(Player* playerPtr);

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    // PolarBear only dies if hit by spear (we will rely on Spear collision to set health)
    void takeDamage(int amount) override;

    void roar();

private:
    float speed = 350.f;
    float attackRange = 28.f;
};
