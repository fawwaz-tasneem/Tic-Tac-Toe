// --- HexBoard.cpp ---
#include "HexBoard.h"

// Constructor: initialize the board with empty spaces.
HexBoard::HexBoard() : board(GRID_SIZE, std::vector<char>(GRID_SIZE, ' ')) {}

// Makes a move if the cell is empty.
bool HexBoard::makeMove(int row, int col, char player) {
    if (board[row][col] == ' ') {
        board[row][col] = player;
        return true;
    }
    return false;
}

// Checks for a simple win condition: three in a row horizontally or vertically.
char HexBoard::checkWinner() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            char player = board[i][j];
            if (player == ' ') continue;
            // Check horizontally.
            if (j + 2 < GRID_SIZE && board[i][j + 1] == player && board[i][j + 2] == player)
                return player;
            // Check vertically.
            if (i + 2 < GRID_SIZE && board[i + 1][j] == player && board[i + 2][j] == player)
                return player;
        }
    }
    return ' ';
}

// Checks if the board is completely filled.
bool HexBoard::isFull() {
    for (const auto& row : board)
        for (char cell : row)
            if (cell == ' ')
                return false;
    return true;
}

// Computes the position of a hexagon based on its row and column.
// This uses an offset layout for the hex grid.
sf::Vector2f HexBoard::getHexPosition(int row, int col) {
    // Calculate the x offset. 1.5 factor spaces hexagons horizontally.
    float xOffset = col * (HEX_SIZE * 1.5f);
    // Calculate the y offset. The 1.732 factor (≈sqrt(3)) spaces them vertically.
    // Offset every other column by half the hexagon height.
    float yOffset = row * (HEX_SIZE * 1.732f) + (col % 2) * (HEX_SIZE * 0.866f);
    return sf::Vector2f(xOffset, yOffset);
}

// Creates and returns a hexagon shape given the position, size, and color.
sf::CircleShape HexBoard::createHexagon(float x, float y, float size, sf::Color color) {
    sf::CircleShape hex(size, 6);  // 6 points for a hexagon.
    hex.setFillColor(color);
    hex.setOutlineColor(sf::Color::Black);
    hex.setOutlineThickness(2);
    hex.setPosition(x, y);
    // Set the origin to the center of the hexagon for proper positioning.
    hex.setOrigin(size, size);
    return hex;
}

// Draws the hexagonal board to the provided render window.
void HexBoard::draw(sf::RenderWindow& window) {
    // Iterate over each cell in the board.
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            // Compute the position for the hexagon.
            sf::Vector2f position = getHexPosition(i, j);
            // Choose the color based on the cell content:
            // 'X' uses AMU_RED, 'O' uses AMU_GREEN, empty uses AMU_WHITE.
            sf::Color cellColor;
            char cell = board[i][j];
            if (cell == 'X') {
                cellColor = AMU_RED;
            } else if (cell == 'O') {
                cellColor = AMU_GREEN;
            } else {
                cellColor = AMU_WHITE;
            }
            // Create the hexagon shape and draw it.
            sf::CircleShape hex = createHexagon(position.x, position.y, HEX_SIZE, cellColor);
            window.draw(hex);
        }
    }
}
