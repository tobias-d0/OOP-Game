#include "ElectronicsBook.h"

ElectronicsBook::ElectronicsBook() : Item("ElectronicsBook")
{
  name = "ElectronicsBook";

  if (!texture.loadFromFile("assets/textures/ElectronicsBook.png"))
  {
    throw std::runtime_error("Failed to load ElectronicsBook texture!");
  }

  sprite.setTexture(texture, true); // true = reset rect
  
  // Set origin to center for proper positioning
  sf::FloatRect bounds = sprite.getLocalBounds();
  sprite.setOrigin(bounds.size / 2.f);
  
  sprite.setScale({0.4f, 0.4f});
  
  // Use setPosition() to update both position and sprite
  setPosition({400.f, 300.f});
}