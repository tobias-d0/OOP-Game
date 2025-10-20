#include <SFML/Graphics.hpp>

class Item
{
private:
    std::string name;
    bool isVisible;

public:
    virtual void use() = 0;
    void setPosition(sf::Vector2f position);
    void render(sf::RenderWindow &window);
};