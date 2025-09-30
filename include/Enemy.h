#pragma once

#include "Entity.h"

class Enemy : public Entity {
 private:
  int damage;
  public:
  int get_damage();
  void set_damage(int damage);
};