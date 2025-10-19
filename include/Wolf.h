#pragma once
#include "Enemy.h"

class Wolf : public Enemy {
public:
    Wolf();
    void takeDamage(int amount) override;
    void howl();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;
};
