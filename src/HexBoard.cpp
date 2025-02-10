// --- HexBoard.cpp ---
#include "HexBoard.h"

sf::Color AMU_GREEN(0, 102, 0);
sf::Color AMU_WHITE(255, 255, 255);

HexBoard::HexBoard() : board(GRID_SIZE, std::vector<char>(GRID_SIZE, ' ')) {}
// Function to calculate hexagon positions on the board
sf::Vector2f HexBoard::getHexPosition(int row, int col) {
    float xOffset = col * (HEX_SIZE * 1.5f + HEX_SPACING);
    float yOffset = row * (HEX_SIZE * 1.732f + HEX_SPACING) + (col % 2) * (HEX_SIZE * 0.866f);
    return sf::Vector2f(xOffset, yOffset);
}

// Function to create hexagon shapes
sf::CircleShape HexBoard::createHexagon(float x, float y, float size, sf::Color color) {
    sf::CircleShape hex(size, 6);
    hex.setFillColor(color);
    hex.setOutlineColor(sf::Color::Black);
    hex.setOutlineThickness(2);
    hex.setPosition(x, y);
    return hex;
}

bool HexBoard::makeMove(int row, int col, char player) {
    if (board[row][col] == ' ') {
        board[row][col] = player;
        return true;
    }
    return false;
}

char HexBoard::checkWinner() {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            char player = board[i][j];
            if (player == ' ') continue;
            if (j + 2 < GRID_SIZE && board[i][j + 1] == player && board[i][j + 2] == player) return player;
            if (i + 2 < GRID_SIZE && board[i + 1][j] == player && board[i + 2][j] == player) return player;
            if (i + 2 < GRID_SIZE && j + 2 < GRID_SIZE && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player) return player;
        }
    }
    return ' ';
}

void HexBoard::draw(sf::RenderWindow& window) {
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            sf::Vector2f position = getHexPosition(i, j);
            sf::CircleShape hex = createHexagon(position.x, position.y, HEX_SIZE, board[i][j] == 'X' ? AMU_WHITE : AMU_GREEN);
            window.draw(hex);
        }
    }
}
