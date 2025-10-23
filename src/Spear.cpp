#include "Spear.h"
#include "Player.h"
#include <iostream>
#include <cmath>

Spear::Spear(const sf::Vector2f &initialPos, float angleRad, float speed,
             Player *ownerPtr, std::vector<Item *> *worldItemsPtr)
    : Item("Spear"), owner(ownerPtr), worldItems(worldItemsPtr), isFlying(true)
{
  if (!texture.loadFromFile("assets/textures/Spear.png"))
    throw std::runtime_error("Failed to load spear texture!");

  sprite.setTexture(texture, true);
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.size / 2.f);
  sprite.setScale({0.5f, 0.5f});
  setPosition(initialPos);

  // initial velocity
  velocity.x = std::cos(angleRad) * speed;
  velocity.y = -std::sin(angleRad) * speed;

  // rotation
  float angle = std::atan2(-velocity.y, velocity.x);
  sprite.setRotation(sf::degrees(-angle * 180.f / 3.14159f));
}

Spear::Spear() : Item("Spear"), isFlying(false)
{
  if (!texture.loadFromFile("assets/textures/Spear.png"))
    throw std::runtime_error("Failed to load spear texture!");

  sprite.setTexture(texture, true);
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.size / 2.f);
  sprite.setScale({0.5f, 0.5f});
}

void Spear::update(float deltaTime)
{
  if (!isFlying)
    return;

  elapsed += deltaTime;

  // gravity
  velocity.y += gravity * deltaTime;
  setPosition(getPosition() + velocity * deltaTime);

  // rotation to match trajectory
  float angle = std::atan2(-velocity.y, velocity.x);
  sprite.setRotation(sf::degrees(-angle * 180.f / 3.14159f));

  // lifetime (remove if too long)
  if (elapsed > 5.f)
    markForRemoval();
}
void Spear::useItem()
{
  if (!owner || !worldItems)
    return;

  std::cout << "Player threw spear\n";

  // Determine throw direction
  sf::Vector2f dir = owner->getVelocity();
  if (dir.x == 0.f && dir.y == 0.f)
    dir = owner->isFacingRight() ? sf::Vector2f{1.f, 0.f} : sf::Vector2f{-1.f, 0.f};
  else
  {
    float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
    if (len > 0.001f)
      dir /= len;
  }

  // --- Throw parameters ---
  float throwSpeed = 700.f;

  // --- Spawn position offset ---
  sf::Vector2f startPos = owner->getPosition() + dir * 40.f; // 40 pixels ahead of player

  // --- Apply projectile motion ---
  isFlying = true;
  velocity = dir * throwSpeed;
  setPosition(startPos);

  // --- Fix rotation (match direction, not inverted) ---
  float angle = std::atan2(dir.y, dir.x);
  sprite.setRotation(sf::degrees(angle * 180.f / 3.14159f));

  elapsed = 0.f;

  // --- Transfer ownership ---
  owner->getInventory().removeItem(this);
  owner->unequipItem();
  worldItems->push_back(this);

  // --- Ensure visibility ---
  setVisible(true);
  setActive(true);
}

void Spear::bind(Player *newOwner, std::vector<Item *> *worldItemsPtr)
{
  owner = newOwner;
  worldItems = worldItemsPtr;
}