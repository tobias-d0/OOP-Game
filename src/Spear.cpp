#include "Spear.h"
#include "Enemy.h"
#include "PolarBear.h"
#include <iostream>

Spear::Spear(const sf::Vector2f& initialPos, float angleRad, float speed, Player* ownerPtr)
: owner(ownerPtr) {
    // init texture if you want (user said they will do rendering)
    if (!texture.loadFromFile("spear.png")) {
        // no texture is fine; user handles rendering if they want
    }
    sprite.setTexture(texture);
    setPosition(initialPos);

    // initial velocity
    velocity.x = std::cos(angleRad) * speed;
    velocity.y = -std::sin(angleRad) * speed; // negative because y increases downward in SFML
}

void Spear::update(float deltaTime) {
    // kinematic update with gravity
    elapsed += deltaTime;
    // update position
    // integrate velocity
    velocity.y += gravity * deltaTime;
    setPosition(getPosition() + velocity * deltaTime);

    // collision check with enemies
    checkCollisions();

    if (elapsed > lifeTime) {
        GameWorld::get().removeProjectile(this);
    }
}

void Spear::render(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Spear::checkCollisions() {
    // check against all enemies
    // brute-force: iterate GameWorld::get().enemies - but enemies are private; we'll rely on GameWorld having friend access
    // To keep it simple, we'll access through the public GameWorld::get() internal vector by adding a small getter (or we'll expose a simple function)
    // To avoid changing GameWorld again, let's query via a temporary method: we'll assume GameWorld has 'enemies' accessible via friend. Simpler: iterate by adding a public accessor.

    // I'll implement a minimal public accessor in GameWorld (you can move it).
    auto& enemiesRef = GameWorld::get().enemies; // note: make 'enemies' public or add accessor (see integration note)
    for (Enemy* e : enemiesRef) {
        if (!e) continue;
        if (!e->isAlive()) continue;
        if (getHitbox().intersects(e->getHitbox())) {
            // If it's a PolarBear -> kill it
            PolarBear* pb = dynamic_cast<PolarBear*>(e);
            if (pb) {
                pb->setHealth(0);
                pb->setAlive(false);
                GameWorld::get().removeEnemy(pb);
                std::cout << "Spear hit polar bear — it's dead!\n";
            } else {
                // normal enemies take damage
                e->takeDamage(50); // spear damage to normal enemies
            }
            // remove spear on hit
            GameWorld::get().removeProjectile(this);
            return;
        }
    }
}
