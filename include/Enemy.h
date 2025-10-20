#pragma once
#include "Entity.h"
#include <string>

class Enemy : public Entity {
protected:
    int damage;
    std::string loot;

public:
    Enemy();

    int getDamage() const;
    void setDamage(int dmg);
    void dropLoot() const;

    virtual void takeDamage(int amount);
};
