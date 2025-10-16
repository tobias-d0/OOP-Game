#include "Player.h"
#include <iostream>

#include "Player.h"
#include <iostream>

Player::Player(Map& mapRef) : map(mapRef) {
    // Initialize position at center
    position = sf::Vector2f(720/2.f, 480/2.f);
    
    // Set up the player shape
    shape.setSize(sf::Vector2f(50.f, 50.f));
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(position);
    
    // Initialize velocity and speed
    velocity = sf::Vector2f(0.f, 0.f);
    speed = 300.f; // Increase speed to make movement more noticeable
}

void Player::handleInput(const sf::Event& event) {
    // Reset velocity each frame
    velocity = sf::Vector2f(0.f, 0.f);
    
    // Check keyboard state
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocity.y = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y = speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x = -speed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x = speed;
    }
}

void Player::update(float deltaTime) {
    // Calculate new position
    sf::Vector2f newPos = position + velocity * deltaTime;
    
    // Update hitbox for collision check
    sf::FloatRect newHitbox = shape.getGlobalBounds();
    newHitbox.left = newPos.x;
    newHitbox.top = newPos.y;
    
    // Update position if no collision
    if (!map.isBlocked(newHitbox)) {
        position = newPos;
        shape.setPosition(position);
    }
    
    // Debug output
    if (velocity.x != 0 || velocity.y != 0) {
        std::cout << "Position: " << position.x << ", " << position.y << std::endl;
    }
}

void Player::render(sf::RenderWindow& window) {
    window.draw(shape);
}