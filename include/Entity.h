#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
protected:
  sf::Sprite sprite;
  sf::Texture texture;
  sf::Vector2f position;
  float speed;
  int health;

public:
  Entity();
  Entity(const sf::Texture &texture);
  virtual ~Entity() = default;

  virtual void update(float deltaTime) = 0;
  virtual void render(sf::RenderWindow &window);
  virtual void takeDamage(int damage) = 0;

  sf::Vector2f getPosition() const { return position; }
  sf::FloatRect getHitbox() const { return sprite.getGlobalBounds(); }
  bool isAlive() const { return health > 0; }
  int getHealth() const { return health; }
  void setTexture(const std::string &path);
};
