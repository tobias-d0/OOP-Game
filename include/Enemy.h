#pragma once
#include "Entity.h"
#include <string>

class Player;

class Enemy : public Entity {
protected:
    int damage;
    std::string loot;
    Player* player; // reference to player
    bool alive = true; // used for despawn
public:
    Enemy(Player* playerPtr = nullptr);

    virtual ~Enemy() = default;

    int getDamage() const;
    void setDamage(int dmg);
    void dropLoot() const;

    virtual void takeDamage(int amount) override;
    virtual void update(float deltaTime) override = 0;

    bool isAlive() const { return alive; }
    void setAlive(bool a) { alive = a; }
};
