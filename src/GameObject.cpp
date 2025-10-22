#include "GameObject.h"
#include <stdexcept>

#include "GameObject.h"
#include <stdexcept>

GameObject::GameObject()
    : sprite(texture),
      position(0.f, 0.f),
      active(true),
      visible(true),
      pendingRemoval(false)
{
  if (!texture.loadFromFile("assets/textures/placeholder.png"))
  {
    throw std::runtime_error("Failed to load placeholder texture!");
  }
  sprite.setTexture(texture);
}

GameObject::GameObject(const std::string &texturePath)
    : sprite(texture),
      position(0.f, 0.f),
      active(true),
      visible(true),
      pendingRemoval(false)
{
  if (!texture.loadFromFile(texturePath))
  {
    if (!texture.loadFromFile("assets/textures/placeholder.png"))
    {
      throw std::runtime_error("Failed to load placeholder texture!");
    }
  }
  sprite.setTexture(texture);
}

void GameObject::render(sf::RenderWindow &window)
{
  if (!visible)
    return;

  window.draw(sprite);
}

void GameObject::setActive(bool state)
{
  active = state;
}

bool GameObject::isActive() const
{
  return active;
}

void GameObject::setVisible(bool state)
{
  visible = state;
}

bool GameObject::isVisible() const
{
  return visible;
}

void GameObject::markForRemoval()
{
  pendingRemoval = true;
}

bool GameObject::isPendingRemoval() const
{
  return pendingRemoval;
}

void GameObject::setPosition(const sf::Vector2f &pos)
{
  position = pos;
  sprite.setPosition(pos);
}

sf::Vector2f GameObject::getPosition() const
{
  return position;
}

sf::FloatRect GameObject::getHitbox() const
{
  return sprite.getGlobalBounds();
}

void GameObject::setTexture(const std::string &path)
{
    if (!texture.loadFromFile(path))
    {
        throw std::runtime_error("Failed to load texture: " + path);
    }

    sprite.setTexture(texture, true);

    // Recalculate size and origin
    size_t width = texture.getSize().x;
    size_t height = texture.getSize().y;
    sprite.setOrigin({width / 2.f, height / 2.f}); // ✅ centers sprite
    sprite.setPosition(position);
}


void GameObject::setScale(sf::Vector2f scale) {
  sprite.setScale(scale);
}