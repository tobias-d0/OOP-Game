#pragma once

#include "UIElement.h"

#include <vector>

class IconOverlay : public UIElement
{
protected:
  sf::Texture iconFullTexture;
  sf::Texture iconEmptyTexture;
  std::vector<sf::Sprite> icons;

  int maxIcons;
  float currentValue;
  float maxValue;
  float spacing;

public:
  IconOverlay(const std::string &iconFullTexPath,
              const std::string &iconEmptyTexPath,
              int maxIcons,
              const sf::Vector2f &position,
              float spacing = 20.f);

  void setValue(float value);
  void update(float deltaTime) override;
  void render(sf::RenderWindow &window) const override;
};