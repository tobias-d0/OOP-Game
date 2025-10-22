#pragma once
#include <SFML/Graphics.hpp>

#include "Entity.h"
#include "Item.h"

#include "Map.h"
#include "Player.h"

#include "HealthOverlay.h"
#include "HungerOverlay.h"

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
  void spawnItems();

  sf::RenderWindow *window;
  sf::Clock *gameClock;
  sf::Clock *framesClock;

  std::vector<Entity *> entities;
  std::vector<Item *> items;

  sf::View camera;
  Map map;
  Player player;

  HealthOverlay health;
  HungerOverlay hunger;

  Spawner spawner;
  sf::Clock spawnClock;

  const unsigned int WINDOW_WIDTH = 720;
  const unsigned int WINDOW_HEIGHT = 480;

  bool isRunning = true;

public:
  GameManager();
  ~GameManager();
  void run();
};
