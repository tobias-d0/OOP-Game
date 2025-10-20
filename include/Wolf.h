#pragma once
#include "Enemy.h"
#include <SFML/System/Clock.hpp>

class Wolf : public Enemy {
public:
    Wolf(Player* playerPtr);

    void update(float deltaTime) override;
    void render(sf::RenderWindow& window) override;

    void takeDamage(int amount) override;
    void howl(); // unique behavior (you can expand)

private:
    float speed = 80.f; // pixels/sec
    float attackRange = 24.f;
    float detectRange = 200.f;

    bool fleeing = false;
    sf::Clock fearClock;
    float fearDuration = 30.f; // seconds to despawn after fear begins

    void chasePlayer(float dt);
    void fleeFromPlayer(float dt);
    float distanceToPlayer() const;
};
