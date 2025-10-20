#pragma once
#include <SFML/Graphics.hpp>


#include "Entity.h"

#include "Map.h"
#include "Player.h"

#include "HealthOverlay.h"
#include "HungerOverlay.h"

class GameManager {
 private:
  void init();
  void processEvents();
  void update(float deltaTime);
  void render();

  sf::RenderWindow* window;
  sf::Clock* gameClock;
  sf::Clock* framesClock;

  std::vector<Entity*> entities;
  sf::View camera;
  Map map;
  Player player;

  HealthOverlay health;
  HungerOverlay hunger;

  const unsigned int WINDOW_WIDTH = 720;
  const unsigned int WINDOW_HEIGHT = 480;

  bool isRunning = true;

 public:
  GameManager();
  ~GameManager();
  void run();
};
