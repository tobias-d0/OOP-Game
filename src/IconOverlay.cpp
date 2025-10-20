#include "IconOverlay.h"
#include <algorithm>
#include <stdexcept>

IconOverlay::IconOverlay(const std::string &iconFullTexPath,
                         const std::string &iconEmptyTexPath,
                         int maxIcons,
                         const sf::Vector2f &position,
                         float spacing)
    : UIElement(position),
      maxIcons(maxIcons),
      currentValue(maxIcons),
      maxValue(static_cast<float>(maxIcons)),
      spacing(spacing)
{
    if (!iconFullTexture.loadFromFile(iconFullTexPath))
        throw std::runtime_error("Failed to load full icon texture: " + iconFullTexPath);

    if (!iconEmptyTexture.loadFromFile(iconEmptyTexPath))
        throw std::runtime_error("Failed to load empty icon texture: " + iconEmptyTexPath);

    icons.reserve(maxIcons);
    for (int i = 0; i < maxIcons; ++i)
    {
        sf::Sprite sprite(iconFullTexture);
        sprite.setScale({0.8f, 0.8f}); // Smaller icons
        sprite.setPosition({position.x + i * spacing, position.y});
        icons.push_back(std::move(sprite));
    }
}

void IconOverlay::setValue(float value)
{
    currentValue = std::clamp(value, 0.f, maxValue);

    for (int i = 0; i < maxIcons; ++i)
    {
        // If current value covers this icon, it’s full; otherwise, empty
        if (i < static_cast<int>(currentValue))
            icons[i].setTexture(iconFullTexture);
        else
            icons[i].setTexture(iconEmptyTexture);
    }
}

void IconOverlay::update(float /*deltaTime*/)
{
    // Optional: could animate flashing when low health/hunger
}

void IconOverlay::render(sf::RenderWindow &window) const
{
    if (!visible)
        return;

    for (const auto &icon : icons)
        window.draw(icon);
}
