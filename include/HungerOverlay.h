#pragma once
#include "IconOverlay.h"

class HungerOverlay : public IconOverlay
{
public:
  HungerOverlay(const sf::Vector2f &position)
      : IconOverlay(
            "assets/textures/Hunger.png",  // full icon
            "assets/textures/HungerEmpty.png", // empty icon
            10,
            position,
            36.f * 0.8)
  {
  }
};
