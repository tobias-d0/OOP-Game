#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class GameObject
{
protected:
  sf::Sprite sprite;
  sf::Texture texture;
  sf::Vector2f position;

  bool active;
  bool visible;
  bool pendingRemoval;

public:
  GameObject();                               // Default
  GameObject(const std::string &texturePath); // With texture
  virtual ~GameObject() {}

  // Core behaviour
  virtual void update(float deltaTime) = 0;
  virtual void render(sf::RenderWindow &window);

  // State control
  void setActive(bool state);
  bool isActive() const;

  void setVisible(bool state);
  bool isVisible() const;

  void markForRemoval();
  bool isPendingRemoval() const;

  // Common functions
  void setPosition(const sf::Vector2f &pos);
  sf::Vector2f getPosition() const;
  sf::FloatRect getHitbox() const;

  void setTexture(const std::string &path);
  void setScale(sf::Vector2f scale);
  sf::Vector2f getScale();
};
