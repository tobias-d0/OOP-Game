#pragma once
#include "Entity.h"
#include "Map.h"
#include "Inventory.h"

class Player : public Entity {
 private:
  sf::Vector2f velocity;
  float speed = 200.f;
  int hunger;
  int warmth;
  Inventory inventory;
  Map& map;
  // In Player.h, add:
  sf::RectangleShape shape;


  // Replace with your asset path
  const std::string PLAYER_TEXTURE_PATH = "assets/textures/Spear.png";

 public:
  Player(Map& map);

  void handleInput(const sf::Event& event);
  void update(float deltaTime) override;
  void render(sf::RenderWindow& window) override;

  void pickUpItem();
  void useItem();
  void craftItem();

  int getHunger();
  void setHunger(int hunger);
  int getWarmth();
  void setWarmth(int warmth);
};
