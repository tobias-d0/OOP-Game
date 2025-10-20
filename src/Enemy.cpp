#include "Enemy.h"
#include "Player.h"
#include <iostream>

Enemy::Enemy(Player* playerPtr) : damage(10), loot("None"), player(playerPtr) {}

int Enemy::getDamage() const { return damage; }
void Enemy::setDamage(int dmg) { damage = dmg; }

void Enemy::dropLoot() const {
    std::cout << "Dropped loot: " << loot << std::endl;
}

void Enemy::takeDamage(int amount) {
    setHealth(getHealth() - amount);
    std::cout << "Enemy took " << amount << " damage! Health: " << getHealth() << std::endl;
    if (getHealth() <= 0) {
        alive = false;
    }
}

void Enemy::render(sf::RenderWindow& window) {
    window.draw(sprite);
}
