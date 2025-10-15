#include "GameManager.h"

#include <iostream>

#include "Map.h"
#include "Player.h"

GameManager::GameManager() : map(), player(map) { init(); }

void GameManager::init() {
  window = new sf::RenderWindow(sf::VideoMode(800, 600), "Arctic Survival");
  window->setFramerateLimit(60);

  // Initialize camera with the same size as the window
  camera.setSize(800, 600);
  camera.setCenter(400, 300);  // Start at center of window
}

void GameManager::run() {
  sf::Clock clock;
  while (window->isOpen()) {
    sf::Time elapsed = clock.restart();
    float deltaTime = elapsed.asSeconds();

    processEvents();
    update(deltaTime);
    render();
  }
}

void GameManager::processEvents() {
  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) window->close();

    player.handleInput(event);
  }
}

void GameManager::update(float deltaTime) {
  player.update(deltaTime);
  
  sf::Vector2f playerPos = player.getPosition();
  camera.setCenter(playerPos);
}

void GameManager::render() {
  window->clear(sf::Color::White);  // white background

  window->setView(camera);

  map.render(*window);

  // Draw the player
  player.render(*window);

  window->display();
}

GameManager::~GameManager() {
  if (window) {
    window->close();
    delete window;  // free memory
    window = nullptr;
  }
}