// --- Game.cpp ---
#include "Game.h"
#include "Colors.cpp"

Game::Game() : window(sf::VideoMode(800, 600), "Hex Tic-Tac-Toe", sf::Style::Close), currentPlayer('X'), gameOver(false) {}

void Game::handleClick(int x, int y) {
    if (gameOver) return;
    int row = y / (HEX_SIZE * 1.732f);
    int col = x / (HEX_SIZE * 1.5f);
    if (row < GRID_SIZE && col < GRID_SIZE && board.makeMove(row, col, currentPlayer)) {
        char winner = board.checkWinner();
        if (winner != ' ') {
            gameOver = true;
            winnerText = "Winner: Player " + std::string(1, winner);
        } else if (board.isFull()) {
            gameOver = true;
            winnerText = "Game Drawn!";
        } else {
            currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
        }
    }
}

void Game::draw() {
    board.draw(window);
    UI::drawText(window, "Player Turn: " + std::string(1, currentPlayer), 20, 20, 24, AMU_RED);
    if (gameOver) {
        UI::drawText(window, winnerText, 250, 550, 30, AMU_GREEN);
    }
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