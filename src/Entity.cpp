#include "Entity.h"
#include <stdexcept>

//default constructor for entity
Entity::Entity()
    : GameObject("assets/textures/placeholder.png"),
      speed(0.f),
      health(10)
{
}

//constructor for entity with specific texture path 
Entity::Entity(const std::string &texturePath)
    : GameObject(texturePath),
      speed(0.f),
      health(10)
{
}

void Entity::render(sf::RenderWindow &window)
{
  window.draw(sprite);
}