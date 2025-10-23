#include <iostream>
#include <sstream>

#include "GameManager.h"

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
#include "Electronics.h"
#include "ElectronicsBook.h"
#include "Radio.h"

GameManager::GameManager() : map(), player(*this, map), health({0, 0}), hunger({100, 0}), spawner(map)
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

  spawnItems(true);
  event2();
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
    textHint->setFontSize(24);
    showHint("YOU DIED");
    std::cout << "Player has died!\n";
  }

  // Don't update game if player is dead
  if (playerDead)
  {
    return;
  }

  if (player.getInventory().hasItem("Radio") && player.getInventory().hasItem("Electronics") && player.getInventory().hasItem("ElectronicsBook"))
  {
    showHint("You crafted the radio and got help!");
    playerWon = true;
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

  if (event1Clock.getElapsedTime().asSeconds() >= 60)
  {
    event1();
    event1Clock.restart();
  }
  if (event2Clock.getElapsedTime().asSeconds() >= 45)
  {
    event2();
    event2Clock.restart();
  }
  if (spawnClock.getElapsedTime().asSeconds() >= 60)
  {
    spawnItems();
    spawnClock.restart();
  }

  checkPlayerBounds(deltaTime);

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
  else if (playerWon)
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
    textHint->render(*window);
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

void GameManager::spawnItems(bool first)
{
  if (first)
  {
  }

  const int NUM_TORCHES = 2;
  const int NUM_SPEARS = 0;

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

  // // Spawn Spears
  // for (int i = 0; i < NUM_SPEARS; ++i)
  // {
  //   Spear *spear = new Spear({0, 0}, 0.f, 100.f, &player, &items);

  //   if (spawner.placeItem(spear))
  //   {
  //     items.push_back(spear);
  //   }
  //   else
  //   {
  //     delete spear;
  //   }
  // }

  Electronics *electronics = new Electronics();

  if (spawner.placeItem(electronics))
  {
    items.push_back(electronics);
  }
  else
  {
    delete electronics;
  }

  ElectronicsBook *electronicsbook = new ElectronicsBook();

  if (spawner.placeItem(electronicsbook))
  {
    items.push_back(electronicsbook);
  }
  else
  {
    delete electronicsbook;
  }
  Radio *radio = new Radio();

  if (spawner.placeItem(radio))
  {
    items.push_back(radio);
  }
  else
  {
    delete radio;
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

void GameManager::event1()
{
  int NUM_WOLVES = 10;
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
}

void GameManager::event2()
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

void GameManager::checkPlayerBounds(float deltaTime)
{

  const float mapW = map.getWidth();
  const float mapH = map.getHeight();
  sf::Vector2f pos = player.getPosition();

  bool outside = false;
  std::string direction;

  // Check horizontal boundaries
  if (pos.x < 0.f)
  {
    outside = true;
    direction = "East";
  }
  else if (pos.x > mapW)
  {
    outside = true;
    direction = "West";
  }

  // Check vertical boundaries
  if (pos.y < 0.f)
  {
    outside = true;
    direction = "South";
  }
  else if (pos.y > mapH)
  {
    outside = true;
    direction = "North";
  }

  if (outside)
  {
    timeOutsideBounds += deltaTime;

    if (timeOutsideBounds < 20.f)
    {
      std::ostringstream msg;
      msg << "You are venturing too far! Turn back " << direction << ".";
      textHint->setFontSize(16);
      showHint(msg.str());
    }
    else if (timeOutsideBounds < 30.f)
    {
      textHint->setFontSize(16);
      showHint("You are succumbing to hypothermia...");
    }
    else
    {
      player.takeDamage(10);
    }
  }
  else
  {
    timeOutsideBounds = 0.f;
  }

  if (hintVisible)
  {
    hintTimer += deltaTime;
    if (hintTimer > hintFadeDelay)
    {
      textHint->setVisible(false);
      hintVisible = false;
    }
  }
}

void GameManager::showHint(const std::string &message)
{
  textHint->setText(message);
  textHint->setVisible(true);
  hintVisible = true;
  hintTimer = 0.f; // reset fade timer
}

sf::RenderWindow *GameManager::getWindow()
{
  return window;
}

std::vector<Item *> *GameManager::getItems()
{
  return &items;
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
    
void GameManager::processEvents() {
    sf::Event event;
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window->close();

        // --- Save/Load controls ---
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::F5) {
                saveGame();
            }

            if (event.key.code == sf::Keyboard::F9) {
                loadGame();
            }
        }
    }
}

*/

