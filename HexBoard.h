// --- HexBoard.h ---
#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <vector>
#include <SFML/Graphics.hpp>

class HexBoard {
public:
    static const int GRID_SIZE = 5; // 5x5 hexagonal grid
    HexBoard();
    bool makeMove(int row, int col, char player);
    char checkWinner();
    void draw(sf::RenderWindow& window);
    bool isFull();

private:
    std::vector<std::vector<char>> board;
    sf::CircleShape createHexagon(float x, float y, float size, sf::Color color);
};

#endif

