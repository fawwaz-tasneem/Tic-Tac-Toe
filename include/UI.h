// UI.h
#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <string>

class UI {
public:
    // Draws centered text at the given (centerX, centerY).
    static void drawText(sf::RenderWindow& window, const std::string& text, int centerX, int centerY, int size, sf::Color color);
};

#endif
