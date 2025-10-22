// Spear.cpp
#include "Spear.h"
#include <iostream>
#include <cmath>

Spear::Spear(const sf::Vector2f &initialPos, float angleRad, float speed, Player *ownerPtr)
    : Item("Spear"), owner(ownerPtr), isFlying(true)
{
  if (!texture.loadFromFile("assets/textures/Spear.png"))
  {
    throw std::runtime_error("Failed to load spear texture!");
  }
  sprite.setTexture(texture);

  // Set origin to center for rotation
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.size / 2.f);

  sprite.setScale({0.5f, 0.5f});
  setPosition(initialPos);

  // initial velocity
  velocity.x = std::cos(angleRad) * speed;
  velocity.y = -std::sin(angleRad) * speed; // negative because y increases downward

  // Rotate sprite to match trajectory
  float angle = std::atan2(-velocity.y, velocity.x);
  sprite.setRotation(sf::degrees(-angle * 180.f / 3.14159f));
}

// Default constructor for world spawns (pickup items)
Spear::Spear() : Item("Spear"), isFlying(false)
{
  if (!texture.loadFromFile("assets/textures/spear.png"))
  {
    throw std::runtime_error("Failed to load spear texture!");
  }
  sprite.setTexture(texture);

  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.size / 2.f);

  sprite.setScale({0.5f, 0.5f});
}

void Spear::update(float deltaTime)
{
  // Only apply physics if it's flying (thrown)
  if (!isFlying)
    return;

  elapsed += deltaTime;

  // Apply gravity
  velocity.y += gravity * deltaTime;

  // Update position
  setPosition(getPosition() + velocity * deltaTime);

  // Update rotation to match trajectory
  float angle = std::atan2(-velocity.y, velocity.x);
  sprite.setRotation(sf::degrees(-angle * 180.f / 3.14159f));

  // Optional: remove after some time or if off-screen
  if (elapsed > 5.f)
  {
    markForRemoval();
  }
}