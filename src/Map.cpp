#include "Map.h"

#include <iostream>

Map::Map() {
  std::cout << "Map started" << std::endl;
  if (!rockTexture.loadFromFile(ROCK_TEXTURE_PATH)) {
    std::cerr << "Error loading rock texture from " << ROCK_TEXTURE_PATH
              << "\n";
  }
  if (!snowTexture.loadFromFile(SNOW_TEXTURE_PATH)) {
    std::cerr << "Error loading snow texture from " << SNOW_TEXTURE_PATH
              << "\n";
  }

  // Create a tiled background (optional; here a single white tile)
  backgroundTile.setTexture(snowTexture);
  backgroundTile.setScale(10.f, 10.f);  // Cover more area

  // Example rocks (obstacles)
  for (int i = 0; i < 5; ++i) {
    Rock rock;
    rock.sprite.setTexture(rockTexture);
    rock.sprite.setPosition(i * 300.f, i * 200.f);
    rock.hitbox = rock.sprite.getGlobalBounds();
    rocks.push_back(rock);
  }
  std::cout << "Map initialised" << std::endl;
}

void Map::render(sf::RenderWindow& window) const {
  // Just a single snow tile background for now
  window.draw(backgroundTile);

  // Draw rocks
  for (const auto& rock : rocks) {
    window.draw(rock.sprite);
  }
}

bool Map::isBlocked(const sf::FloatRect& hitbox) const {
  for (const auto& rock : rocks) {
    if (rock.hitbox.intersects(hitbox)) return true;
  }
  return false;
}
