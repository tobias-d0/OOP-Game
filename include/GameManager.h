#pragma once
#include <SFML/Graphics.hpp>

#include "Map.h"
#include "Player.h"

class GameManager {
 private:
  void init();
  void processEvents();
  void update(float deltaTime);
  void render();

  sf::RenderWindow* window;
  // sf::View camera;
  Map map;
  Player player;

  const unsigned int WINDOW_WIDTH = 720;
  const unsigned int WINDOW_HEIGHT = 480;

  bool isRunning = true;

 public:
  GameManager();
  ~GameManager();
  void run();
};
