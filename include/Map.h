#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Map {
public:
    Map();

    void render(sf::RenderWindow& window) const;
    bool isBlocked(const sf::FloatRect& hitbox) const;

private:
    struct Rock {
        sf::Sprite sprite;
        sf::FloatRect hitbox;
    };

    std::vector<Rock> rocks;
    sf::Texture rockTexture;
    sf::Texture snowTexture;
    sf::Sprite backgroundTile;

    // Replace with your asset paths
    const std::string ROCK_TEXTURE_PATH = "assets/textures/RockSimple.png";
    const std::string SNOW_TEXTURE_PATH = "assets/textures/SnowPile.png";
};
