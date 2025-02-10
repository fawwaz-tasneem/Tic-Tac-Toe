// UI.h
#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>
#include <string>

class UI {
public:
    // Draws centered text at the given (centerX, centerY) using the standard font.
    // The optional 'scale' parameter (default 1.0) allows animated scaling.
    static void drawText(sf::RenderWindow& window, const std::string& text,
                         int centerX, int centerY, int size, sf::Color color, float scale = 1.0f);
    
    // Draws centered winner text using a cursive font.
    static void drawWinnerText(sf::RenderWindow& window, const std::string& text,
                               int centerX, int centerY, int size, sf::Color color, float scale = 1.0f);
};

#endif
