#include "PolarBear.h"
#include "Player.h"
#include <cmath>
#include <iostream>

PolarBear::PolarBear(Player *playerPtr) : Enemy(playerPtr)
{
  if (!texture.loadFromFile("assets/textures/PolarBear.png"))
  {
    std::cout << "Error loading PolarBear.png\n";
  }
  sprite.setTexture(texture);
  setHealth(50);
  setDamage(5);
}

void PolarBear::update(float deltaTime)
{
  if (!player)
    return;
  sf::Vector2f dir = player->getPosition() - getPosition();
  float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
  if (len > 0.001f)
  {
    dir /= len;
    setPosition(getPosition() + dir * speed * deltaTime);
  }
  // attack if close
  if (len < attackRange)
  {
    player->takeDamage(getDamage());
  }
}

void PolarBear::render(sf::RenderWindow &window)
{
  window.draw(sprite);
}

void PolarBear::takeDamage(int amount)
{
  health -= amount / 2;
}

void PolarBear::roar()
{
  std::cout << "Polar bear roars.\n";
}
