// UI.cpp
#include "UI.h"
#include <iostream>

void UI::drawText(sf::RenderWindow& window, const std::string& text, int centerX, int centerY, int size, sf::Color color) {
    static sf::Font font;
    static bool isFontLoaded = false;
    if (!isFontLoaded) {
        if (!font.loadFromFile("../assets/arial.ttf")) {
            std::cerr << "Failed to load font assets/arial.ttf" << std::endl;
            return;
        }
        isFontLoaded = true;
    }
    
    sf::Text uiText;
    uiText.setFont(font);
    uiText.setString(text);
    uiText.setCharacterSize(size);
    uiText.setFillColor(color);
    
    sf::FloatRect textRect = uiText.getLocalBounds();
    uiText.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    uiText.setPosition(static_cast<float>(centerX), static_cast<float>(centerY));
    
    window.draw(uiText);
}
