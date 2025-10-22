#include "Wolf.h"
#include "Player.h"
#include <cmath>
#include <iostream>

Wolf::Wolf(Player* playerPtr) : Enemy(playerPtr) {
    if (!texture.loadFromFile("assets/textures/Wolf.png")) {
        std::cout << "Error loading wolf.png\n";
    }
    sprite.setTexture(texture);
    setHealth(30);
}

float Wolf::distanceToPlayer() const {
    if (!player) return 1e6f;
    sf::Vector2f diff = getPosition() - player->getPosition();
    return std::sqrt(diff.x*diff.x + diff.y*diff.y);
}

void Wolf::chasePlayer(float dt) {
    if (!player) return;
    sf::Vector2f dir = player->getPosition() - getPosition();
    float len = std::sqrt(dir.x*dir.x + dir.y*dir.y);
    if (len > 0.001f) {
        dir /= len;
        setPosition(getPosition() + dir * speed * dt);
    }
}

void Wolf::fleeFromPlayer(float dt) {
    if (!player) return;
    sf::Vector2f dir = getPosition() - player->getPosition(); // away from player
    float len = std::sqrt(dir.x*dir.x + dir.y*dir.y);
    if (len > 0.001f) {
        dir /= len;
        setPosition(getPosition() + dir * speed * dt);
    }
}

void Wolf::update(float deltaTime) {
    if (!player) return;
    float dist = distanceToPlayer();

    // If player has torch and close enough, flee
    if (player->getInventory().hasItem("Torch") && dist < detectRange) {
        if (!fleeing) {
            fleeing = true;
            fearClock.restart();
            std::cout << "Wolf scared by torch, fleeing!\n";
        }
        fleeFromPlayer(deltaTime);
        // If fear time exceeded -> despawn
        if (fearClock.getElapsedTime().asSeconds() > fearDuration) {
            // mark for removal
            setAlive(false);
            markForRemoval();
            std::cout << "Wolf despawned after fear duration.\n";
            return;
        }
        return;
    }

    // else normal behavior
    if (dist < detectRange) {
        chasePlayer(deltaTime);

        // attack if close
        if (dist < attackRange) {
            if (player) {
                player->takeDamage(damage);
            }
        }
    } else {
        // idle / patrol - here we don't implement patrol, could wander in future
    }
}

void Wolf::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Wolf::takeDamage(int amount) {
    std::cout << "Wolf snarls in pain.\n";
    Enemy::takeDamage(amount);
    if (!isAlive()) {
        markForRemoval();
    }
}

void Wolf::howl() {
    std::cout << "Wolf howls.\n";
}
