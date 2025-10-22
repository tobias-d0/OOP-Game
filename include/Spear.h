#pragma once
#include "Entity.h"
#include <SFML/System/Clock.hpp>

class Spear : public Item {
public:
    // initialPos: world position where spear is thrown from
    // angleRad: angle in radians above horizontal
    // speed: initial speed magnitude
    // lifeTime: max lifetime (s)
    Spear(const sf::Vector2f& initialPos, float angleRad, float speed, Player* owner);

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Vector2f velocity; // current velocity (px/sec)
    float gravity = 980.f; // px/s^2 (tweak as needed)
    float lifeTime = 5.f;
    float elapsed = 0.f;
    Player* owner = nullptr;

    void checkCollisions();
};
