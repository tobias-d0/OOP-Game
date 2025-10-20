#pragma once
#include "Enemy.h"

class PolarBear : public Enemy {
public:
    PolarBear();  // Constructor with texture
    void takeDamage(int amount) override;
    void roar();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
