#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Item
{
protected:
    std::string name;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f position;
    sf::Vector2u size;
    bool isVisible;

public:
    Item();

    sf::Vector2f getPosition() const { return position; }
    sf::Vector2u getSize() const { return size; }
    sf::FloatRect getHitbox() const { return sprite.getGlobalBounds(); }
    virtual void use() = 0;
    void setPosition(sf::Vector2f position);
    virtual void useItem() = 0;
    void render(sf::RenderWindow &window);
    std::string getName();

    void setTexture(const std::string &path);
};