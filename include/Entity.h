#pragma once
#include <SFML/Graphics.hpp>

class Entity {
 private:
  int health;

 public:
  Entity();
  virtual ~Entity() = default;

  virtual void update(float deltaTime) = 0;
  virtual void render(sf::RenderWindow& window) = 0;

  sf::Vector2f getPosition() const { return position; }
  sf::FloatRect getHitbox() const { return sprite.getGlobalBounds(); }
  int getHealth() const { return health; }

  void setPosition(sf::Vector2f position);

  // virtual void takeDamage() = 0;
  bool isAlive() const;
  void setHealth(int health);

 protected:
  sf::Sprite sprite;
  sf::Texture texture;
  sf::Vector2f position;
};
