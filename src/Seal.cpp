#include "Seal.h"
#include <iostream>

Seal::Seal() {
    if (!texture.loadFromFile("seal.png")) {
        std::cout << "Error loading seal.png" << std::endl;
    }
    sprite.setTexture(texture);
}

void Seal::takeDamage(int amount) {
    std::cout << "Seal takes damage.\n";
    Enemy::takeDamage(amount);
}

void Seal::dive() {
    std::cout << "Seal dives underwater and avoids damage!\n";
}

void Seal::update(float deltaTime) {
    // Optional: swim logic
}

void Seal::render(sf::RenderWindow& window) {
    window.draw(sprite);
}
