// --- UI.cpp ---
#include "UI.h"

void UI::drawText(sf::RenderWindow& window, const std::string& text, int x, int y, int size, sf::Color color) {
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) return;
    sf::Text uiText;
    uiText.setFont(font);
    uiText.setString(text);
    uiText.setCharacterSize(size);
    uiText.setFillColor(color);
    uiText.setPosition(x, y);
    window.draw(uiText);
}
