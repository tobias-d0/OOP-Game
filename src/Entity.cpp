#include "Entity.h"

Entity::Entity() : health(100), position(0.f, 0.f) {}

void Entity::setPosition(sf::Vector2f pos) {
    position = pos;
    sprite.setPosition(pos);
}

void Entity::setHealth(int h) {
    health = h;
}

bool Entity::isAlive() const {
    return health > 0;
}
