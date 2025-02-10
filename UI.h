#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>

class UI {
public:
    static void drawText(sf::RenderWindow& window, const std::string& text, int x, int y, int size, sf::Color color);
};

#endif
