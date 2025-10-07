#include "Player.h"

#include <iostream>

Player::Player(Map& mapRef) : map(mapRef) {
  // In Player.cpp constructor:
  position = sf::Vector2f(720/2.f, 480/2.f);
  shape.setSize(sf::Vector2f(50.f, 50.f));  // 50x50 square
  shape.setFillColor(sf::Color::Red);
  shape.setPosition(position);



  // if (!texture.loadFromFile(PLAYER_TEXTURE_PATH)) {
  //   std::cerr << "Error loading player texture from " << PLAYER_TEXTURE_PATH
  //             << "\n";
  // }
  // sprite.setTexture(texture);
  // sprite.setScale(0.5f, 0.5f);
  // position = {0.f, 0.f};
  // sprite.setPosition(position);
}

void Player::handleInput(const sf::Event& event) {
  // Using real-time input (not event-based)
  velocity = {0.f, 0.f};

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) velocity.y -= speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) velocity.y += speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) velocity.x -= speed;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) velocity.x += speed;
}

void Player::update(float deltaTime) {
  sf::Vector2f newPos = position + velocity * deltaTime;
  sf::FloatRect newHitbox = shape.getGlobalBounds();
  newHitbox.left = newPos.x;
  newHitbox.top = newPos.y;

  // Collision check with map obstacles
  if (!map.isBlocked(newHitbox)) {
    position = newPos;
    sprite.setPosition(position);
  }
}

void Player::render(sf::RenderWindow& window) { window.draw(shape); }
