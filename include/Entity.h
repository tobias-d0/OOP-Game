#pragma once
#include "GameObject.h"

class Entity : public GameObject
{
protected:
    float speed;
    int health;

public:
    Entity();                              // Uses placeholder
    Entity(const std::string &texturePath); // Uses provided texture
    virtual ~Entity() = default;

    // Core behaviour
    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window);

    // Combat / health
    virtual void takeDamage(int damage) = 0;

    // Accessors
    bool isAlive() const { return health > 0; }
    int getHealth() const { return health; }
    void setHealth(int h) { health = h; }

    void setSpeed(float s) { speed = s; }
    float getSpeed() const { return speed; }
};
