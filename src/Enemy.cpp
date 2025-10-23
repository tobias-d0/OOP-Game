#include "Enemy.h"
#include "Player.h"
#include <iostream>

Enemy::Enemy(Player* playerPtr) : damage(10), loot("None"), player(playerPtr) {} //set default constructor

int Enemy::getDamage() const { return damage; } //return damage for getter
void Enemy::setDamage(int dmg) { damage = dmg; } //set damage to passed value

void Enemy::dropLoot() const {
    std::cout << "Dropped loot: " << loot << std::endl; //print out dropped loot
}

//function to apply damage to enemy health
void Enemy::takeDamage(int amount) {
    setHealth(getHealth() - amount); //reduce health by damage amount
    std::cout << "Enemy took " << amount << " damage! Health: " << getHealth() << std::endl; 
    if (getHealth() <= 0) {
        alive = false; //if health is less than 0, mark enemy as not alive
    }
}