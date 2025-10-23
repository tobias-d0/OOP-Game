#include "Electronics.h"

Electronics::Electronics() : Item("Electronics")
{
  name = "Electronics";

  if (!texture.loadFromFile("assets/textures/Electronics.png"))
  {
    throw std::runtime_error("Failed to load Electronics texture!");
  }

  sprite.setTexture(texture, true); // true = reset rect
  
  // Set origin to center for proper positioning
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.size / 2.f);
  
  sprite.setScale({0.5f, 0.5f});
  
  // Use setPosition() to update both position and sprite
  setPosition({400.f, 300.f});
}