#pragma once
#include "Item.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Player;

class Spear : public Item
{
public:
    // For thrown spears
    Spear(const sf::Vector2f &initialPos,
          float angleRad,
          float speed,
          Player *ownerPtr,
          std::vector<Item *> *worldItems);

    // For ground (pickup) spears
    Spear();

    void update(float deltaTime) override;
    void useItem() override;

    void setFlying(bool flying) { isFlying = flying; }
    bool isProjectile() const { return isFlying; } // used by GameManager
    float getDamage() const { return damage; }

    void bind(Player *newOwner, std::vector<Item *> *worldItemsPtr);

private:
    Player *owner = nullptr;
    std::vector<Item *> *worldItems = nullptr; // pointer to GameManager's items list

    sf::Vector2f velocity;
    float gravity = 100.f;
    float elapsed = 0.f;
    bool isFlying = false;
    float damage = 20.f;
};
