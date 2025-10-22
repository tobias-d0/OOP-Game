#include "Map.h"
#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

Map::Map()
    : width(800*8), height(600*8), background(snowTexture)
{
  // Load snow texture
  if (!snowTexture.loadFromFile(SNOW_TEXTURE_PATH))
  {
    std::cerr << "Error loading snow texture from " << SNOW_TEXTURE_PATH << "\n";
  }
  snowTexture.setRepeated(true);
  background.setTexture(snowTexture);

  // Load rock texture
  if (!rockTexture.loadFromFile(ROCK_TEXTURE_PATH))
  {
    std::cerr << "Error loading rock texture from " << ROCK_TEXTURE_PATH << "\n";
  }

  // Generate random rock formations
  generateRocks();
}

#include <cstdlib>
#include <ctime>

void Map::generateRocks()
{
  srand(static_cast<unsigned>(time(nullptr)));

  // Increase the number of clusters (6–10 instead of 2–5)
  int clusterCount = 6 + rand() % 5; // 6–10 clusters total

  for (int i = 0; i < clusterCount; ++i)
  {
    // Choose a random cluster centre — now spaced farther apart from borders
    float centerX = 200.f + static_cast<float>(rand() % (width - 400));
    float centerY = 200.f + static_cast<float>(rand() % (height - 400));

    // Each cluster has more rocks now (3–7)
    int rockCount = 3 + rand() % 5; // 3–7 rocks per cluster

    for (int j = 0; j < rockCount; ++j)
    {
      sf::Sprite rock(rockTexture);

      // Rocks spread farther from cluster centre (±80 px instead of ±25)
      float offsetX = static_cast<float>((rand() % 161) - 80); // -80 → +80
      float offsetY = static_cast<float>((rand() % 161) - 80);

      float x = centerX + offsetX;
      float y = centerY + offsetY;
      rock.setPosition({x, y});

      // Random scale (slightly varied sizes)
      float scale = 0.8f + static_cast<float>(rand() % 61) / 100.f; // 0.8–1.4×
      rock.setScale({scale, scale});
      
      // Prevent overlapping rocks (simple bounding-box check)
      const sf::FloatRect newBox = rock.getGlobalBounds();
      bool overlap = false;

      for (const auto &existing : rocks)
      {
        auto intersection = existing.getGlobalBounds().findIntersection(newBox);
        if (intersection.has_value())
        {
          overlap = true;
          break;
        }
      }

      if (!overlap)
        rocks.push_back(rock);
    }
  }
}

bool Map::intersectsExisting(const sf::FloatRect &newBox) const
{
  for (const auto &rock : rocks)
  {
    const sf::FloatRect existing = rock.getGlobalBounds();
    auto intersection = existing.findIntersection(newBox);
    if (intersection.has_value())
      return true;
  }
  return false;
}

bool Map::isBlocked(const sf::FloatRect &hitbox) const
{
  for (const auto &rock : rocks)
  {
    const sf::FloatRect existing = rock.getGlobalBounds();
    if (existing.findIntersection(hitbox).has_value())
      return true;
  }
  return false;
}

void Map::render(sf::RenderWindow &window, const sf::View &view)
{
  sf::Vector2f center = view.getCenter();
  sf::Vector2f size = view.getSize();

  sf::Vector2f topLeft(center.x - size.x / 2.f, center.y - size.y / 2.f);
  background.setPosition(topLeft);
  background.setTextureRect(sf::IntRect(
      sf::Vector2i(static_cast<int>(topLeft.x), static_cast<int>(topLeft.y)),
      sf::Vector2i(static_cast<int>(size.x), static_cast<int>(size.y))));

  window.draw(background);

  // Draw rocks
  for (const auto &rock : rocks)
    window.draw(rock);
}

int Map::getWidth() const { return width; }
int Map::getHeight() const { return height; }
