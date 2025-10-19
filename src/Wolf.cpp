#include "Wolf.h"
#include <iostream>

Wolf::Wolf() {
    if (!texture.loadFromFile("wolf.png")) {
        std::cout << "Error loading wolf.png" << std::endl;
    }
    sprite.setTexture(texture);
}

void Wolf::takeDamage(int amount) {
    std::cout << "Wolf snarls in pain.\n";
    Enemy::takeDamage(amount);
}

void Wolf::howl() {
    std::cout << "Wolf howls, calling the pack!\n";
}

void Wolf::update(float deltaTime) {
    // Optional: patrol logic
}

void Wolf::render(sf::RenderWindow& window) {
    window.draw(sprite);
}
