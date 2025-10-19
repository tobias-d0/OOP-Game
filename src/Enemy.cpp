
#include "Enemy.h"
#include <iostream>

Enemy::Enemy() : damage(10), loot("None") {}

int Enemy::getDamage() const {
    return damage;
}

void Enemy::setDamage(int dmg) {
    damage = dmg;
}

void Enemy::dropLoot() const {
    std::cout << "Dropped loot: " << loot << std::endl;
}

void Enemy::takeDamage(int amount) {
    setHealth(getHealth() - amount);
    std::cout << "Enemy took " << amount << " damage! Health: " << getHealth() << std::endl;
}
