#include "GameManager.h"

#include <iostream>

#include "Map.h"
#include "Player.h"
#include "Entity.h"
#include "HealthOverlay.h"
#include "HungerOverlay.h"
#include "TextHint.h"
#include "Enemy.h"
#include "Item.h"
#include "Spawner.h"
#include "Wolf.h"
#include "PolarBear.h"

#include "Torch.h"
#include "Spear.h"

GameManager::GameManager() : map(), player(map), health({0, 0}), hunger({100, 0}), spawner(map)
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

  // Initialize death screen elements
  textHint = new TextHint(window, "", 48);
  textHint->setVisible(false);

  blackOverlay.setSize({static_cast<float>(windowSize.x), static_cast<float>(windowSize.y)});
  blackOverlay.setFillColor(sf::Color::Black);
  blackOverlay.setPosition({0.f, 0.f});

  spawnItems();
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

  if (player.getHealth() <= 0 && !playerDead)
  {
    playerDead = true;
    textHint->setText("YOU DIED");
    textHint->setVisible(true);
    std::cout << "Player has died!\n";
  }

  // Don't update game if player is dead
  if (playerDead)
  {
    return;
  }

  for (Entity *entity : entities)
  {
    entity->update(deltaTime);
  }

  for (Item *item : items)
  {
    item->update(deltaTime);
  }

  camera.setCenter(player.getPosition());

  health.setValue(player.getHealth());
  hunger.setValue(player.getHunger());

  checkItemDropped();
  checkItemPickup();

  cleanupGameObjects();
}

// In GameManager.cpp - update render():
void GameManager::render()
{
  window->clear();

  if (playerDead)
  {
    // Death screen - black background with text
    window->setView(window->getDefaultView());
    window->draw(blackOverlay);
    textHint->render(*window);
  }
  else
  {
    // Normal game rendering
    window->setView(camera);

    map.render(*window, camera);

    for (Entity *entity : entities)
    {
      entity->render(*window);
    }

    for (Item *item : items)
    {
      item->render(*window);
    }

    window->setView(window->getDefaultView());
    health.render(*window);
    hunger.render(*window);
  }

  window->display();
}
void GameManager::addEntity(Entity *e)
{
  entities.push_back(e);
}

void GameManager::removeEntity(Entity *e)
{
  e->markForRemoval();
}

void GameManager::addItem(Item *i)
{
  items.push_back(i);
}

void GameManager::removeItem(Item *i)
{
  i->markForRemoval();
}

void GameManager::checkItemPickup()
{
  sf::FloatRect playerBox = player.getHitbox();

  for (int i = items.size() - 1; i >= 0; --i)
  {
    Item *item = items[i];
    if (!item || !item->isActive())
      continue;

    sf::FloatRect itemBox = item->getHitbox();

    if (playerBox.findIntersection(itemBox))
    {
      // They overlap!
      player.pickUpItem(item);

      item->markForRemoval();
      std::cout << "Picked up " << item->getName() << "\n";
    }
  }
}

void GameManager::checkItemDropped()
{
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q))
  {
    Item *dropped = player.dropSelectedItem();
    if (dropped)
    {
      dropped->setPosition(player.getPosition());
      dropped->setActive(true);
      dropped->setVisible(true);
      addItem(dropped);
    }
  }
}

void GameManager::cleanupGameObjects()
{
  // Clean up entities marked for removal
  for (int i = entities.size() - 1; i >= 0; --i)
  {
    if (entities[i]->isPendingRemoval())
    {
      delete entities[i];
      entities.erase(entities.begin() + i);
    }
  }

  // Clean up items marked for removal (but don't delete inventory ones)
  for (int i = items.size() - 1; i >= 0; --i)
  {
    if (items[i]->isPendingRemoval())
    {
      // DO NOT delete items — player might have it in inventory
      items.erase(items.begin() + i);
    }
  }
}

void GameManager::spawnItems()
{
  const int NUM_TORCHES = 5;
  const int NUM_SPEARS = 3;

  // Spawn Torches
  for (int i = 0; i < NUM_TORCHES; ++i)
  {
    Torch *torch = new Torch();

    if (spawner.placeItem(torch))
    {
      items.push_back(torch);
    }
    else
    {
      delete torch;
    }
  }

  // Spawn Spears
  for (int i = 0; i < NUM_SPEARS; ++i)
  {
    Spear *spear = new Spear();

    if (spawner.placeItem(spear))
    {
      items.push_back(spear);
    }
    else
    {
      delete spear;
    }
  }
}

void GameManager::checkSpearCollisions()
{
  // Check all spears against all entities
  for (int i = items.size() - 1; i >= 0; --i)
  {
    Item *item = items[i];
    if (!item || !item->isActive())
      continue;

    // Check if it's a flying spear
    Spear *spear = dynamic_cast<Spear *>(item);
    if (!spear || !spear->isProjectile())
      continue;

    sf::FloatRect spearBox = spear->getHitbox();

    // Check collision with entities
    for (int j = entities.size() - 1; j >= 0; --j)
    {
      Entity *entity = entities[j];
      if (!entity || !entity->isActive())
        continue;

      // Don't hit the player
      if (entity == &player)
        continue;

      sf::FloatRect entityBox = entity->getHitbox();

      if (spearBox.findIntersection(entityBox))
      {
        // Hit something!
        entity->takeDamage(spear->getDamage());

        std::cout << "Spear hit entity for " << spear->getDamage() << " damage!\n";

        // Remove the spear
        spear->markForRemoval();
        break;
      }
    }
  }
}

void GameManager::spawnEnemies()
{
  const int NUM_WOLVES = 2;
  const int NUM_POLAR_BEARS = 1;

  // Spawn Wolves
  for (int i = 0; i < NUM_WOLVES; ++i)
  {
    Wolf *wolf = new Wolf(&player);

    if (spawner.placeEntity(wolf))
    {
      entities.push_back(wolf);
    }
    else
    {
      delete wolf;
    }
  }

  // Spawn Polar Bears
  for (int i = 0; i < NUM_POLAR_BEARS; ++i)
  {
    PolarBear *bear = new PolarBear(&player);

    if (spawner.placeEntity(bear))
    {
      entities.push_back(bear);
    }
    else
    {
      delete bear;
    }
  }
}

GameManager::~GameManager()
{
  cleanupGameObjects();
  if (window)
  {
    window->close();
    delete window; // free memory
    window = nullptr;
  }
}

/*
void GameManager::saveGame() {
    std::ofstream file("save.txt");

    if (!file.is_open()) {
        std::cout << "Error opening save file.\n";
        return;
    }

    // Get player data
    int health = player.getHealth();
    int hunger = player.getHunger();
    int warmth = player.getWarmth();
    sf::Vector2f pos = player.getPosition();

    // Write data in plain text
    file << health << " "
         << pos.x << " " << pos.y << " "
         << hunger << " "
         << warmth << "\n";

    file.close();
    std::cout << "Game saved successfully.\n";
}

void GameManager::loadGame() {
    std::ifstream file("save.txt");

    if (!file.is_open()) {
        std::cout << "No save file found.\n";
        return;
    }

    int health, hunger, warmth;
    float posX, posY;

    // Read data back
    file >> health >> posX >> posY >> hunger >> warmth;

    // Reapply to player
    player.setHealth(health);
    player.setHunger(hunger);
    player.setWarmth(warmth);
    player.setPosition(sf::Vector2f(posX, posY));

    file.close();
    std::cout << "Game loaded successfully.\n";
}

*/

