#pragma once
#include "Enemy.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class PolarBear : public Enemy
{
public:
    PolarBear(Player *playerPtr);

    void update(float deltaTime) override;

    // PolarBear only dies if hit by spear (we will rely on Spear collision to set health)
    void takeDamage(int amount) override;

    void roar();

private:
    enum class State
    {
        Idle,
        Chasing,
        Dashing,
        Cooldown
    };
    State state = State::Idle;

    sf::Vector2f dashDirection;
    sf::Clock dashClock;
    sf::Clock cooldownClock;

    sf::SoundBuffer roarBuffer;
    sf::Sound roarSound;

    float attackRange = 80.f;
    float dashRange = 300.f;
    float dashDuration = 1.f; // dash lasts 1 second
    float dashSpeed = 400.f;   // speed during dash
    float normalSpeed = 200.f; // normal chase speed
    float dashCooldown = 2.0f; // seconds between dashes
};
