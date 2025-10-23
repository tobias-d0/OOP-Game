#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Item.h"

#include "Map.h"
#include "Player.h"

#include "HealthOverlay.h"
#include "HungerOverlay.h"
#include "TextHint.h"

#include "Item.h"
#include "Spawner.h"

class GameManager
{
private:
  void init();
  void processEvents();
  void update(float deltaTime);
  void render();
  void addEntity(Entity *e);
  void removeEntity(Entity *e);
  void addItem(Item *i);
  void removeItem(Item *i);
  void checkItemPickup();
  void checkItemDropped();
  void cleanupGameObjects();
  void spawnItems(bool first = false);
  void checkSpearCollisions();
  void showHint(const std::string &message);
  void checkPlayerBounds(float deltaTime);
  // void spawnEnemies();

  void event1();
  void event2();
  //void saveGame();
  //void loadGame();
  //void processEvents()

  sf::RenderWindow *window;
  sf::Clock *gameClock;
  sf::Clock *framesClock;
  sf::Clock event1Clock;
  sf::Clock event2Clock;
  sf::Clock spawnClock;

  std::vector<Entity *> entities;
  std::vector<Item *> items;

  sf::View camera;
  Map map;
  Player player;

  HealthOverlay health;
  HungerOverlay hunger;

  Spawner spawner;

  TextHint *textHint;
  float hintTimer = 0.f;
  bool hintVisible = false;
  const float hintFadeDelay = 5.f;
  bool playerWon;

  float timeOutsideBounds = 0.f;

  bool playerDead = false;
  sf::RectangleShape blackOverlay;

  const unsigned int WINDOW_WIDTH = 720;
  const unsigned int WINDOW_HEIGHT = 480;

  bool isRunning = true;

public:
  GameManager();
  sf::RenderWindow* getWindow();
  std::vector<Item*>* getItems();
  ~GameManager();
  void run();
};
