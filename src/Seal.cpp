#include "Seal.h"
#include <iostream>

Seal::Seal() {
    if (!texture.loadFromFile("Seal.png")) {
        std::cout << "Error loading Seal.png" << std::endl;
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
}

void Seal::render(sf::RenderWindow& window) {
    window.draw(sprite);
}
