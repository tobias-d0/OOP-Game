// #include <SFML/Window.hpp>
// #include <SFML/System.hpp>
// #include <SFML/Graphics.hpp>

// #include "GameManager.h"

// int main() {
//     GameManager game;
//     game.run();
//     return 0;
// }

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Smooth Movement");

    // Either limit FPS *or* enable VSync (not both at the same time).
    window.setFramerateLimit(60);
    // window.setVerticalSyncEnabled(true); // Optionally use instead of framerate

    sf::playerShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.f, 275.f);

    const float speed = 200.f; // Movement speed in pixels per second

    sf::Clock clock; // For delta time

   while (window.pollEvent(event))
{
        if (event.type == sf::Event::Closed)
                window.close();
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        player.move(0, -0.5);
        y -= 0.05;
        cout << x << ", " << y << endl;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        player.move(0, 0.5);
        y += 0.05;
        cout << x << ", " << y << endl;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        player.move(-0.5, 0);
        x -= 0.05;
        cout << x << ", " << y << endl;
}
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        player.move(0.5, 0);
        x += 0.05;
        cout << x << ", " << y << endl;
}
 

    return 0;
}
