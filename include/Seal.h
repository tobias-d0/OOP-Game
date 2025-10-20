#pragma once
#include "Enemy.h"

class Seal : public Enemy {
public:
    Seal();
    void takeDamage(int amount) override;
    void dive();
    void update(float deltaTime) override;
};
