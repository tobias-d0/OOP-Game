#include "Wolf.h"
#include "Player.h"
#include <cmath>
#include <iostream>

Wolf::Wolf(Player *playerPtr) : Enemy(playerPtr), howlSound(howlBuffer)
{
    if (!texture.loadFromFile("assets/textures/Wolf.png"))
    {
        std::cout << "Error loading wolf.png\n";
    }

    if (!howlBuffer.loadFromFile("assets/sounds/wolfHowl.wav"))
        throw std::runtime_error("Failed to load wolfHowl.wav!");

    howlSound.setBuffer(howlBuffer);
    howlSound.setVolume(60.f);

    sprite.setTexture(texture, true);
    sprite.setScale({1.3f, 1.3f});

    sf::FloatRect bounds = sprite.getLocalBounds();
    sprite.setOrigin({static_cast<float>(bounds.size.x) / 2.f, static_cast<float>(bounds.size.y) / 2.f});

    setHealth(30);
    setDamage(static_cast<int>(damage));
}

void Wolf::update(float deltaTime)
{
    if (!player)
        return;

    sf::Vector2f toPlayer = player->getPosition() - getPosition();
    float dist = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);
    sf::Vector2f dir = (dist > 0.001f) ? toPlayer / dist : sf::Vector2f{0.f, 0.f};

    // --- Torch fear mechanic ---
    if (player->getEquippedItem()->getName() == "Torch" && dist < detectRange)
    {
        if (!fleeing)
        {
            fleeing = true;
            state = State::Fleeing;
            fearClock.restart();
            howlSound.play(); // frightened howl
            std::cout << "Wolf frightened by torch! Running away...\n";
        }
    }

    if (fleeing)
    {
        // Run away from player
        sf::Vector2f fleeDir = -dir; // opposite direction
        setPosition(getPosition() + fleeDir * normalSpeed * 1.5f * deltaTime);
        sprite.setPosition(getPosition());

        if (fearClock.getElapsedTime().asSeconds() > fleeDuration)
        {
            std::cout << "Wolf despawned after fear duration.\n";
            markForRemoval();
            return;
        }

        // Flip sprite visually
        sprite.setScale({(fleeDir.x >= 0 ? -1.3f : 1.3f), 1.3f});
        return;
    }

    // --- Normal / dash attack behavior ---
    switch (state)
    {
    case State::Idle:
    case State::Chasing:
    {
        // Begin dash if close enough and cooldown expired
        if (dist < dashRange && cooldownClock.getElapsedTime().asSeconds() > dashCooldown)
        {
            state = State::Dashing;
            dashDirection = dir;
            dashClock.restart();
            cooldownClock.restart();
            howl();
            break;
        }

        // Regular chase
        setPosition(getPosition() + dir * normalSpeed * deltaTime);
        sprite.setPosition(getPosition());
        break;
    }

    case State::Dashing:
    {
        setPosition(getPosition() + dashDirection * dashSpeed * deltaTime);
        sprite.setPosition(getPosition());

        if (dashClock.getElapsedTime().asSeconds() > dashDuration)
        {
            state = State::Cooldown;
            dashClock.restart();
        }
        break;
    }

    case State::Cooldown:
    {
        if (dashClock.getElapsedTime().asSeconds() > 0.4f)
        {
            state = State::Chasing;
        }
        break;
    }

    default:
        break;
    }

    // Flip sprite orientation based on movement
    sprite.setScale({(dir.x >= 0 ? -1.3f : 1.3f), 1.3f});

    // Damage player if overlapping
    if (player->getHitbox().findIntersection(this->getHitbox()))
    {
        player->takeDamage(static_cast<int>(damage));
    }
}

void Wolf::render(sf::RenderWindow &window)
{
    window.draw(sprite);
}

void Wolf::takeDamage(int amount)
{
    std::cout << "Wolf yelps in pain!\n";
    Enemy::takeDamage(amount);
    if (!isAlive())
    {
        markForRemoval();
    }
}

void Wolf::howl()
{
    if (howlSound.getStatus() != sf::Sound::Status::Playing)
        howlSound.play();
}
