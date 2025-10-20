#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "GameManager.h"

int main() {
    GameManager game;
    game.run();
    return 0;
}


// int main() {
//     // Create an SFML window (SFML 3 syntax)
//     sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML 3 - WASD Movement");
//     window.setFramerateLimit(60);

//     // Create a controllable square
//     sf::RectangleShape square({50.f, 50.f});
//     square.setFillColor(sf::Color::Green);
//     square.setPosition({375.f, 275.f});

//     const float speed = 250.f;  // Pixels per second
//     sf::Clock clock;

//     // Main game loop
//     while (window.isOpen()) {
//         // Process events (SFML 3 API)
//         while (const std::optional<sf::Event> event = window.pollEvent()) {
//             // Handle window close
//             if (event->is<sf::Event::Closed>())
//                 window.close();
//         }

//         // Time since last frame
//         float dt = clock.restart().asSeconds();

//         // Handle input
//         sf::Vector2f movement{0.f, 0.f};
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= speed * dt;
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += speed * dt;
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= speed * dt;
//         if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += speed * dt;

//         // Move square
//         square.move(movement);

//         // Render everything
//         window.clear(sf::Color::Black);
//         window.draw(square);
//         window.display();
//     }

// Wolf* w = new Wolf(GameWorld::get().getPlayer());
//w->setPosition({100, 100});
//GameWorld::get().addEnemy(w);

//Seal* s = new Seal(GameWorld::get().getPlayer());
//s->setPosition({200, 200});
//GameWorld::get().addEnemy(s);

//     return 0;
// }
