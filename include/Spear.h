// Spear.h
#pragma once
#include "Item.h"
#include <SFML/System/Clock.hpp>

class Player;

class Spear : public Item {
public:
    // initialPos: world position where spear is thrown from
    // angleRad: angle in radians above horizontal
    // speed: initial speed magnitude
    Spear(const sf::Vector2f& initialPos, float angleRad, float speed, Player* owner);
    
    // Default constructor for spawning spears as pickups
    Spear();

    void update(float deltaTime) override;
    
    float getDamage() const { return damage; }
    bool isProjectile() const { return isFlying; }

private:
    sf::Vector2f velocity; // current velocity (px/sec)
    float gravity = 980.f; // px/s^2
    float elapsed = 0.f;
    Player* owner = nullptr;
    float damage = 50.f;
    bool isFlying = false; // true when thrown, false when pickup
};