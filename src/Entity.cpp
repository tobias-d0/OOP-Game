#include "Entity.h"

Entity::Entity() 
    : sprite(texture), position(0.f, 0.f), health(10)
{
    if (!texture.loadFromFile("assets/textures/placeholder.png")) {
        throw std::runtime_error("Failed to load placeholder texture!");
    }

    sprite.setTexture(texture);
    sprite.setPosition(position);
}

Entity::Entity(const sf::Texture &texture)
    : sprite(texture), position(0.f, 0.f), health(10)
{
  sprite.setPosition(position);
}

void Entity::render(sf::RenderWindow &window)
{
  window.draw(sprite);
}

void Entity::setTexture(const std::string& path) {
    if (!texture.loadFromFile(path)) {
        throw std::runtime_error("Failed to load texture: " + path);
    }
    sprite.setTexture(texture);
}
