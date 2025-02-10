// --- UI.cpp ---
#include "UI.h"
#include <iostream>
static sf::Font font;
static bool isFontLoaded = false;

void UI::drawText(sf::RenderWindow& window, const std::string& text, int x, int y, int size, sf::Color color) {
    // Load the font once
    if (!isFontLoaded) {
        if (!font.loadFromFile("assets/arial.ttf")) {  // Update path as needed
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
    uiText.setPosition(x, y);
    window.draw(uiText);
}