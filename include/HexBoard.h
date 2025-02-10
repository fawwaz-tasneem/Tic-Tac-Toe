// HexBoard.h
#ifndef HEXBOARD_H
#define HEXBOARD_H

#include <vector>
#include <SFML/Graphics.hpp>

const int BOARD_RADIUS = 2;      // A board with side length 3 (radius 2) gives 19 cells
const float HEX_SIZE = 50.0f;      // Hexagon “radius” (distance from center to vertex)
const float HEX_SPACING = 0.0f;    // No extra spacing (cells share walls)

extern sf::Color AMU_RED;
extern sf::Color AMU_GREEN;
extern sf::Color AMU_WHITE;

// Structure representing a single hex cell in axial coordinates.
struct HexCell {
    int q;       // axial coordinate q
    int r;       // axial coordinate r
    char value;  // ' ' (empty), 'X', or 'O'
};

class HexBoard {
public:
    HexBoard();
    // Attempt to place a move at axial coordinates (q, r)
    bool makeMove(int q, int r, char player);
    // Check for a winner (three consecutive cells in any direction)
    char checkWinner();
    // Draw all hex cells to the window using the provided offset (to center the board)
    void draw(sf::RenderWindow& window, const sf::Vector2f& offset);
    // Returns true if every cell is occupied.
    bool isFull();
    // Returns a reference to the vector of cells (for mouse click detection).
    std::vector<HexCell>& getCells();
    // Convert axial coordinates (q, r) to pixel coordinates (for flat-topped hexes)
    sf::Vector2f axialToPixel(int q, int r);
    
private:
    std::vector<HexCell> cells;
};

#endif
