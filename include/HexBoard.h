// --- HexBoard.h ---
#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <vector>
#include <SFML/Graphics.hpp>

const int GRID_SIZE = 5;
const float HEX_SIZE = 50.0f;
const float HEX_SPACING = 5.0f;

extern sf::Color AMU_RED;
extern sf::Color AMU_GREEN;
extern sf::Color AMU_WHITE;

class HexBoard {
public:
    HexBoard();
    bool makeMove(int row, int col, char player);
    char checkWinner();
    void draw(sf::RenderWindow& window);
    bool isFull();

private:
    std::vector<std::vector<char>> board;
    sf::Vector2f getHexPosition(int row, int col);
    sf::CircleShape createHexagon(float x, float y, float size, sf::Color color);
};

#endif