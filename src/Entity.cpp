#include "Entity.h"
#include <stdexcept>

Entity::Entity()
    : GameObject("assets/textures/placeholder.png"),
      speed(0.f),
      health(10)
{
}

Entity::Entity(const std::string &texturePath)
    : GameObject(texturePath),
      speed(0.f),
      health(10)
{
}