#pragma once
#include "Entity.h" 
#include <string>

class Player; //declaration of player class to enable pointer usage 

class Enemy : public Entity {
protected:
    int damage; //damage enemy can inflict
    std::string loot; //loot dropped by enemy when killed
    Player* player; // reference to player
    bool alive = true; // used for despawn
public:
    Enemy(Player* playerPtr = nullptr); //constructor 

    virtual ~Enemy() = default; //destructor

    int getDamage() const; //getter for damage
    void setDamage(int dmg); //setter for damage
    void dropLoot() const; //function to drop loot

    virtual void takeDamage(int amount) override; // Override takeDamage from Entity
    virtual void update(float deltaTime) override = 0; // Forces derived enemies to implement their own update logic

    bool isAlive() const { return alive; } //check if enemy is alive
    void setAlive(bool a) { alive = a; } //set if enemy alives
};
