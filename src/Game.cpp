// --- Game.cpp ---
#include "Game.h"

Game::Game() : window(sf::VideoMode(600, 600), "Hex Tic-Tac-Toe", sf::Style::Close), currentPlayer('X') {}

void Game::handleClick(int x, int y) {
    int row = y / (HEX_SIZE * 1.732f + HEX_SPACING);
    int col = x / (HEX_SIZE * 1.5f + HEX_SPACING);
    if (row < GRID_SIZE && col < GRID_SIZE && board.makeMove(row, col, currentPlayer)) {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

void Game::draw() {
    window.clear(AMU_GREEN);
    board.draw(window);
    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed)
                handleClick(event.mouseButton.x, event.mouseButton.y);
        }
        draw();
    }
}
