#pragma once
#include "GameObject.h"

//parent class for all entities (enemy and player), inherits from game object
class Entity : public GameObject
{
protected:
    float speed; //movement speed of entity
    int health; //health of entity

public:
    Entity(); //default constructor                         
    Entity(const std::string &texturePath); // Uses provided texture
    virtual ~Entity() = default; //destructor

    // Core behaviour
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window);

    // Combat / health
    virtual void takeDamage(int damage) = 0;

    // Accessors
    bool isAlive() const { return health > 0; }
    int getHealth() const { return health; }
    void setHealth(int h) { health = h; }

    //getter and setter for float/speed
    void setSpeed(float s) { speed = s; }
    float getSpeed() const { return speed; }
};
