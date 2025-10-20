#pragma once
#include "IconOverlay.h"

class HealthOverlay : public IconOverlay
{
public:
  HealthOverlay(const sf::Vector2f &position)
      : IconOverlay(
            "assets/textures/Heart.png",      // full icon
            "assets/textures/HeartEmpty.png", // empty icon
            10,                         // total hearts
            position,
            36.f * 0.8 // spacing between icons
        )
  {
  }
};
