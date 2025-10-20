#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map();

    void render(sf::RenderWindow& window, const sf::View& view);
    bool isBlocked(const sf::FloatRect& hitbox) const;

    int getWidth() const;
    int getHeight() const;

private:
    int width;
    int height;

    sf::Texture snowTexture;
    sf::Sprite background;

    const std::string SNOW_TEXTURE_PATH = "assets/textures/SnowTile.png";
};

