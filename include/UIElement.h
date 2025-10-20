#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class UIElement {
protected:
    sf::Vector2f position;
    bool visible = true;

public:
    UIElement(const sf::Vector2f& position = {0.f, 0.f})
        : position(position) {}
    virtual ~UIElement() = default;

    virtual void update(float deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) const = 0;

    virtual void setPosition(const sf::Vector2f& pos) { position = pos; }
    virtual sf::Vector2f getPosition() const { return position; }

    virtual void setVisible(bool v) { visible = v; }
    virtual bool isVisible() const { return visible; }
};
