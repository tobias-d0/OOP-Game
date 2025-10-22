// TextHint.cpp
#include "TextHint.h"
#include <stdexcept>

TextHint::TextHint(sf::RenderWindow *window, const std::string &initialText, unsigned int characterSize)
    : UIElement({0.f, 0.f}), windowRef(window), text(font, "", characterSize)
{
  if (!font.openFromFile("assets/fonts/AzeretMono[wght].ttf"))
  {
    throw std::runtime_error("Failed to load font");
  }

  text.setFont(font);
  text.setString(initialText);
  text.setCharacterSize(characterSize);
  text.setFillColor(sf::Color::White);

  updatePosition();
}

void TextHint::setText(const std::string &newText)
{
  text.setString(newText);
  updatePosition();
}

void TextHint::update(float deltaTime)
{
  // Currently nothing dynamic; could add animations here
}

void TextHint::render(sf::RenderWindow &window) const
{
  if (visible)
  {
    window.draw(text);
  }
}

void TextHint::setPosition(const sf::Vector2f &pos)
{
  position = pos;
  text.setPosition(position);
}

void TextHint::updatePosition()
{
  if (!windowRef)
    return;

  sf::FloatRect bounds = text.getLocalBounds();
  float x = (windowRef->getSize().x - bounds.size.x) / 2.f - bounds.position.x;
  float y = 10.f; // 10 pixels from top
  setPosition({x, y});
}