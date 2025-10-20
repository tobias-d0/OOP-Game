#include "GameManager.h"

#include <iostream>

#include "Map.h"
#include "Player.h"
#include "Entity.h"
#include "HealthOverlay.h"
#include "HungerOverlay.h"
#include "Enemy.h"

GameManager::GameManager() : map(), player(map), health({0, 0}), hunger({100, 0})
{
  init();
}

void GameManager::init()
{
  window = new sf::RenderWindow(
      sf::VideoMode({800, 600}),
      "Arctic Survival",
      sf::Style::Titlebar | sf::Style::Close);

  window->setFramerateLimit(60);

  framesClock = new sf::Clock;
  gameClock = new sf::Clock;

  entities.push_back(&player);

  camera.setSize({800.f, 600.f});   // same as window size
  camera.setCenter({400.f, 300.f}); // initial center

  const sf::Vector2u windowSize = window->getSize();

  // 10 px margin from window edges
  float margin = 10.f;
  float iconHeight = 36.f * 0.8f;

  // health in bottom-left, hunger in bottom-right
  health = HealthOverlay({margin, windowSize.y - iconHeight - margin});
  hunger = HungerOverlay({windowSize.x - (10 * 36.f * 0.8f) - margin, windowSize.y - iconHeight - margin});

  health.setValue(player.getHealth());
  hunger.setValue(player.getHunger());
}

void GameManager::run()
{
  while (window->isOpen())
  {

    processEvents();
    float deltatime = framesClock->restart().asSeconds();
    update(deltatime);
    render();
  }
}

void GameManager::processEvents()
{
  while (const std::optional<sf::Event> event = window->pollEvent())
  {
    // Handle window close
    if (event->is<sf::Event::Closed>())
      window->close();

    player.handleInput(*event);
  }
}

void GameManager::update(float deltaTime)
{
  for (Entity *entity : entities)
  {
    entity->update(deltaTime);
  }

  camera.setCenter(player.getPosition());

  health.setValue(player.getHealth());
  hunger.setValue(player.getHunger());
}

void GameManager::render()
{
  window->setView(camera);

  map.render(*window, camera);

  for (Entity *entity : entities)
  {
    entity->render(*window);
  }

  window->setView(window->getDefaultView());
  health.render(*window);
  hunger.render(*window);

  window->display();
}

GameManager::~GameManager()
{
  if (window)
  {
    window->close();
    delete window; // free memory
    window = nullptr;
  }
}

void GameManager::addEnemy(Enemy* e) {
    enemies.push_back(e);
}

void GameManager::removeEnemy(Enemy* e) {
    pendingRemovals.push_back(e);
}

void GameManager::addProjectile(Entity* p) {
    projectiles.push_back(p);
}

void GameManager::removeProjectile(Entity* p) {
    pendingProjRemovals.push_back(p);
}

void GameManager::spawnPolarBearAt(const sf::Vector2f& pos) {
    PolarBear* pb = new PolarBear(player);
    pb->setPosition(pos);
    addEnemy(pb);
    std::cout << "PolarBear spawned at (" << pos.x << ", " << pos.y << ")\n";
}

void GameManager::update(float dt) {
    // update enemies
    for (Enemy* e : enemies) {
        if (e) e->update(dt);
    }

    // update projectiles
    for (Entity* p : projectiles) {
        if (p) p->update(dt);
    }

    // cleanup enemies
    for (Enemy* rem : pendingRemovals) {
        auto it = std::find(enemies.begin(), enemies.end(), rem);
        if (it != enemies.end()) {
            delete *it;
            enemies.erase(it);
        }
    }
    pendingRemovals.clear();

    // cleanup projectiles
    for (Entity* rem : pendingProjRemovals) {
        auto it = std::find(projectiles.begin(), projectiles.end(), rem);
        if (it != projectiles.end()) {
            delete *it;
            projectiles.erase(it);
        }
    }
    pendingProjRemovals.clear();
}