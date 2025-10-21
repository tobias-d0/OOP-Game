#pragma once
#include <SFML/Graphics.hpp>


#include "Entity.h"
#include "Item.h" 

#include "Map.h"
#include "Player.h"

#include "HealthOverlay.h"
#include "HungerOverlay.h"

#include "Item.h"
#include "ItemSpawner.h"

class GameManager {
 private:
  void init();
  void processEvents();
  void update(float deltaTime);
  void render();

  // void addEnemy(Enemy* e);
  // void removeEnemy(Enemy* e); // marks for deletion
  // void spawnPolarBearAt(const sf::Vector2f& pos);
  // void checkItemPickup();

  // void addProjectile(Entity* p);
  // void removeProjectile(Entity* p);  

  sf::RenderWindow* window;
  sf::Clock* gameClock;
  sf::Clock* framesClock;

  std::vector<Entity*> entities;
  std::vector<Item*> items;


  sf::View camera;
  Map map;
  Player player;

  HealthOverlay health;
  HungerOverlay hunger;

  ItemSpawner itemSpawner;

  const unsigned int WINDOW_WIDTH = 720;
  const unsigned int WINDOW_HEIGHT = 480;

  bool isRunning = true;

 public:
  GameManager();
  ~GameManager();
  void run();
};
