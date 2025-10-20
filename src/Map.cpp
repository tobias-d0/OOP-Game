#include "Map.h"

#include <iostream>

Map::Map() : width(1600), height(1200), background(snowTexture)
{
  if (!snowTexture.loadFromFile(SNOW_TEXTURE_PATH))
  {
    std::cerr << "Error loading snow texture from " << SNOW_TEXTURE_PATH << "\n";
  }

  snowTexture.setRepeated(true);

  background.setTexture(snowTexture);
}

void Map::render(sf::RenderWindow &window, const sf::View &view)
{
  sf::Vector2f center = view.getCenter();
  sf::Vector2f size = view.getSize();

  // Calculate top-left corner of visible area
  sf::Vector2f topLeft(center.x - size.x / 2.f, center.y - size.y / 2.f);

  // Position sprite at top-left of view
  background.setPosition(topLeft);

  // Offset the texture rect so pattern stays centered visually
  background.setTextureRect(sf::IntRect(
      sf::Vector2i(static_cast<int>(topLeft.x), static_cast<int>(topLeft.y)),
      sf::Vector2i(static_cast<int>(size.x), static_cast<int>(size.y))));

  window.draw(background);
}

bool Map::isBlocked(const sf::FloatRect &hitbox) const
{
  // for (const auto& rock : rocks) {
  //   if (rock.hitbox.intersects(hitbox)) return true;
  // }
  return false;
}

int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }