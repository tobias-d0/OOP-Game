#include "Item.h"

#include <SFML/Graphics.hpp>

Item::Item() : sprite(texture), position({0.f, 0.f}), isVisible(true)
{
  if (!texture.loadFromFile("assets/textures/placeholder.png"))
  {
    throw std::runtime_error("Failed to load placeholder texture!");
  }

  sprite.setTexture(texture);
  sprite.setPosition(position);

  size = texture.getSize();
}

void Item::setPosition(sf::Vector2f position)
{
  this->position = position;
}

void Item::render(sf::RenderWindow &window)
{
  if (isVisible)
  {
    window.draw(sprite);
  }
}

void Item::setTexture(const std::string &path)
{
  if (!texture.loadFromFile(path))
  {
    throw std::runtime_error("Failed to load texture: " + path);
  }
  sprite.setTexture(texture);
}
