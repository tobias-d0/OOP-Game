#pragma once
#include "GameObject.h"
#include <string>

class Item : public GameObject
{
protected:
    std::string name;
    sf::Vector2u size;

public:
    Item(const std::string &name);
    Item(const std::string &name, const std::string &texturePath);
    virtual ~Item() = default;

    // Core behaviour
    virtual void update(float deltaTime) override {}
    // virtual void useItem() = 0;

    // Common accessors
    std::string getName() const { return name; }
    sf::Vector2u getSize() const { return size; }
};
