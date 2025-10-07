#include <iostream>

#include "GameManager.h"

GameManager::GameManager()
    : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Arctic Survival"),
      map(),
      player(map) {

    std::cout << "Window created successfully\n";

    window.setFramerateLimit(60);

    // Initialize camera
    camera.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    camera.setCenter(player.getPosition());
}

void GameManager::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void GameManager::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        player.handleInput(event);
    }
}

void GameManager::update(float deltaTime) {
    player.update(deltaTime);

    // Center camera on player
    // camera.setCenter(player.getPosition());
}

void GameManager::render() {
    window.clear(sf::Color::White);  // white background

    window.setView(camera);

    // Map is empty for now
    map.render(window);

    // Draw the player
    player.render(window);

    window.display();
}
