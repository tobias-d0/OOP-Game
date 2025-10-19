#include "PolarBear.h"
#include <iostream>

PolarBear::PolarBear() {
    if (!texture.loadFromFile("polar_bear.png")) {
        std::cout << "Error loading polar_bear.png" << std::endl;
    }
    sprite.setTexture(texture);
}

void PolarBear::takeDamage(int amount) {
    std::cout << "Polar Bear resists cold damage!\n";
    Enemy::takeDamage(amount / 2);
}

void PolarBear::roar() {
    std::cout << "Polar Bear roars fiercely!\n";
}

void PolarBear::update(float deltaTime) {
    // Optional: movement or AI
}

void PolarBear::render(sf::RenderWindow& window) {
    window.draw(sprite);
}
