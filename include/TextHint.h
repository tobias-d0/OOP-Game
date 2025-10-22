#pragma once
#include "UIElement.h"
#include <SFML/Graphics.hpp>
#include <string>

class TextHint : public UIElement {
private:
    sf::Text text;
    sf::Font font;
    sf::RenderWindow* windowRef = nullptr; // Reference to window for top-center positioning

public:
    TextHint(sf::RenderWindow* window, const std::string& initialText = "", unsigned int characterSize = 24)
        : UIElement({0.f, 0.f}), windowRef(window), text(font, "", 22)
    {
        if (!font.openFromFile("assets/fonts/AzeretMono[wght].ttf")) {
            throw std::runtime_error("Failed to load font");
        }
        text.setFont(font);
        text.setString(initialText);
        text.setCharacterSize(characterSize);
        text.setFillColor(sf::Color::White);

        updatePosition();
    }

    void setText(const std::string& newText) {
        text.setString(newText);
        updatePosition();
    }

    void update(float deltaTime) override {
        // Currently nothing dynamic; could add animations here
    }

    void render(sf::RenderWindow& window) const override {
        if (visible) {
            window.draw(text);
        }
    }

    void setPosition(const sf::Vector2f& pos) override {
        position = pos;
        text.setPosition(position);
    }

    // Centers the text at the top of the window
    void updatePosition() {
        if (!windowRef) return;

        sf::FloatRect bounds = text.getLocalBounds();
        float x = (windowRef->getSize().x - bounds.size.x) / 2.f - bounds.position.x;
        float y = 10.f; // 10 pixels from top
        setPosition({x, y});
    }
};
