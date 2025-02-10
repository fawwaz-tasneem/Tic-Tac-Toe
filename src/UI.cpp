// UI.cpp
#include "UI.h"
#include <iostream>

// Standard font for general UI text.
void UI::drawText(sf::RenderWindow& window, const std::string& text,
                  int centerX, int centerY, int size, sf::Color color, float scale) {
    static sf::Font font;
    static bool isFontLoaded = false;
    if (!isFontLoaded) {
        if (!font.loadFromFile("assets/Arial.ttf")) {
            std::cerr << "Failed to load font assets/Arial.ttf" << std::endl;
            return;
        }
        isFontLoaded = true;
    }
    
    sf::Text uiText;
    uiText.setFont(font);
    uiText.setString(text);
    uiText.setCharacterSize(size);
    uiText.setFillColor(color);
    
    // Center the text.
    sf::FloatRect textRect = uiText.getLocalBounds();
    uiText.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    uiText.setPosition(static_cast<float>(centerX), static_cast<float>(centerY));
    
    // Apply scaling for animation.
    uiText.setScale(scale, scale);
    
    // Draw a drop shadow for improved visibility.
    sf::Text shadowText = uiText;
    shadowText.setFillColor(sf::Color::Black);
    shadowText.move(2, 2);
    window.draw(shadowText);
    
    window.draw(uiText);
}

// Winner text drawn with a cursive font.
void UI::drawWinnerText(sf::RenderWindow& window, const std::string& text,
                        int centerX, int centerY, int size, sf::Color color, float scale) {
    static sf::Font cursiveFont;
    static bool isCursiveLoaded = false;
    if (!isCursiveLoaded) {
        if (!cursiveFont.loadFromFile("assets/Cursive.ttf")) {
            std::cerr << "Failed to load font assets/Cursive.ttf" << std::endl;
            return;
        }
        isCursiveLoaded = true;
    }
    
    sf::Text winnerText;
    winnerText.setFont(cursiveFont);
    winnerText.setString(text);
    winnerText.setCharacterSize(size);
    winnerText.setFillColor(color);
    
    // Center the text.
    sf::FloatRect textRect = winnerText.getLocalBounds();
    winnerText.setOrigin(textRect.left + textRect.width / 2.0f,
                         textRect.top + textRect.height / 2.0f);
    winnerText.setPosition(static_cast<float>(centerX), static_cast<float>(centerY));
    
    winnerText.setScale(scale, scale);
    
    // Draw a drop shadow.
    sf::Text shadowText = winnerText;
    shadowText.setFillColor(sf::Color::Black);
    shadowText.move(2, 2);
    window.draw(shadowText);
    
    window.draw(winnerText);
}
