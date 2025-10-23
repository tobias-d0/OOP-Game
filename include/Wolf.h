#pragma once
#include "Enemy.h"
#include <SFML/System/Clock.hpp>
#include <SFML/Audio.hpp>

class Wolf : public Enemy
{
public:
    Wolf(Player *playerPtr);

    void update(float deltaTime) override;
    void render(sf::RenderWindow &window) override;
    void takeDamage(int amount) override;
    void howl();

private:
    enum class State
    {
        Idle,
        Chasing,
        Dashing,
        Fleeing,
        Cooldown
    };
    State state = State::Idle;

    sf::Vector2f dashDirection;
    sf::Clock dashClock;
    sf::Clock cooldownClock;
    sf::Clock fearClock;

    sf::SoundBuffer howlBuffer;
    sf::Sound howlSound;

    float attackRange = 40.f;
    float detectRange = 200.f;
    float dashRange = 250.f;

    float dashDuration = 0.8f; // slightly shorter than polar bear
    float dashSpeed = 350.f;   // slightly slower than polar bear
    float normalSpeed = 220.f; // faster than polar bear chase
    float dashCooldown = 1.5f; // shorter cooldown
    float fleeDuration = 10.f; // time before despawn
    float damage = 4.f;

    bool fleeing = false;
};
