#include "PolarBear.h"
#include "Player.h"
#include <cmath>
#include <iostream>

PolarBear::PolarBear(Player* playerPtr) : Enemy(playerPtr) {
    if (!texture.loadFromFile("polar_bear.png")) {
        std::cout << "Error loading polar_bear.png\n";
    }
    sprite.setTexture(texture);
    setHealth(200);
    setDamage(30);
}

void PolarBear::update(float deltaTime) {
    if (!player) return;
    sf::Vector2f dir = player->getPosition() - getPosition();
    float len = std::sqrt(dir.x*dir.x + dir.y*dir.y);
    if (len > 0.001f) {
        dir /= len;
        setPosition(getPosition() + dir * speed * deltaTime);
    }
    // attack if close
    if (len < attackRange) {
        player->takeDamage(getDamage());
    }
}

void PolarBear::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void PolarBear::takeDamage(int amount) {
    // ignore normal damage (must be killed by spear). We'll say normal attacks do nothing
    std::cout << "Polar Bear grunts — it's immune to that attack. Use spear!\n";
    // If you later want partial damage from other attacks, call Enemy::takeDamage(amount/whatever)
}

void PolarBear::roar() {
    std::cout << "Polar bear roars.\n";
}
