#pragma once

#include <SFML/Audio.hpp>

#include "Entity.h"
#include "Map.h"
#include "Inventory.h"

class GameManager;

enum class PlayerState
{
  Idle,
  Walking
};

class Player : public Entity
{
private:
  GameManager &gameManager;
  sf::Vector2f velocity;
  int hunger;
  int warmth;
  Inventory inventory;
  sf::RenderWindow* window;
  Map &map;

  bool damageImmune = false;
  sf::Clock immuneClock;
  float immuneDuration = 1.f; // 1 seconds of invulnerability

  sf::Clock hungerClock;
  float hungerDrainDuration = 60.f; // every 60 seconds a hunger bar drains

  sf::Texture idleTexture;
  sf::Texture walkTexture;

  PlayerState state = PlayerState::Idle;
  bool facingRight = true;

  const std::string PLAYER_IDLE_PATH = "assets/textures/PlayerIdle.png";
  const std::string PLAYER_WALK_PATH = "assets/textures/PlayerWalk.png";

  sf::Clock animationClock;
  float animationInterval = 0.2f;

  sf::SoundBuffer damageBuffer;
  sf::SoundBuffer walkBuffer;
  sf::Sound damageSound;
  sf::Sound walkSound;

  sf::Clock walkSoundClock;
  float walkSoundInterval = 4.4f; // audio duration

  sf::Clock regenClock;
  float regenDelay = 2.f;

  int itemNumberSelected = -1; // -1 is no item
  Item *equippedItem = nullptr;

public:
  Player(GameManager &gm, Map &map);

  GameManager &getGameManager() { return gameManager; }
  void handleInput(const sf::Event &event);
  void update(float deltaTime) override;
  void render(sf::RenderWindow &window) override;
  void takeDamage(int damage) override;

  sf::Vector2f getVelocity() { return velocity; }
  bool isFacingRight() { return facingRight; }

  void useItem();
  void craftItem();

  // getters and settings for members specific to player
  int getHunger();
  void setHunger(int hunger);
  int getWarmth();
  void setWarmth(int warmth);

  Inventory &getInventory() { return inventory; }
  bool pickUpItem(Item *item);
  Item *dropItem();
  void displayInventory();
  int getItemIndexSelected();
  Item *getItemSelected();
  Item *dropSelectedItem();

  void equipItem(int index);
  void unequipItem();
  Item *getEquippedItem() const;
};
