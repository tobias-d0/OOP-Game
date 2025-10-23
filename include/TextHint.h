// TextHint.h
#pragma once
#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <string>

class TextHint : public UIElement
{
private:
  sf::Font font;
  sf::Text text;
  sf::RenderWindow *windowRef;
  void updatePosition();

public:
  TextHint(sf::RenderWindow *window, const std::string &initialText = "", unsigned int characterSize = 24);
  
  void setText(const std::string &newText);
  void update(float deltaTime) override;
  void render(sf::RenderWindow &window) const override;
  void setPosition(const sf::Vector2f &pos) override;
  void setFontSize(int fontSize);
};