#include "Seal.h"
#include "Player.h"
#include <cmath>
#include <iostream>

Seal::Seal(Player* playerPtr) : Enemy(playerPtr) {
    if (!texture.loadFromFile("seal.png")) {
        std::cout << "Error loading seal.png\n";
    }
    sprite.setTexture(texture);
    setHealth(20);
}

void Seal::update(float deltaTime) {
    if (!player) return;
    float dx = player->getPosition().x - getPosition().x;
    float dy = player->getPosition().y - getPosition().y;
    float dist = std::sqrt(dx*dx + dy*dy);

    if (dist < fleeRange) {
        // flee away from player
        sf::Vector2f dir = getPosition() - player->getPosition();
        float len = std::sqrt(dir.x*dir.x + dir.y*dir.y);
        if (len > 0.001f) {
            dir /= len;
            setPosition(getPosition() + dir * speed * deltaTime);
        }
    }
}

void Seal::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Seal::takeDamage(int amount) {
    std::cout << "Seal took " << amount << " damage.\n";
    Enemy::takeDamage(amount);
    if (!isAlive()) {
        // spawn polar bear at seal death position
        GameManager::get().spawnPolarBearAt(getPosition());
        GameManager::get().removeEnemy(this);
        std::cout << "Seal died — polar bear will spawn.\n";
    }
}
