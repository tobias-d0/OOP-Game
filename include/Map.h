#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Map
{
public:
    Map();

    void render(sf::RenderWindow &window, const sf::View &view);
    bool isBlocked(const sf::FloatRect &hitbox) const;

    int getWidth() const;
    int getHeight() const;

private:
    int width = 6400;
    int height = 4800;

    sf::Texture snowTexture;
    sf::Texture rockTexture;
    
    sf::Sprite background;
    std::vector<sf::Sprite> rocks;

    const std::string ROCK_TEXTURE_PATH = "assets/textures/RockSimple.png";
    const std::string SNOW_TEXTURE_PATH = "assets/textures/SnowTile.png";

    void generateRocks();
    bool intersectsExisting(const sf::FloatRect &newBox) const;
};
