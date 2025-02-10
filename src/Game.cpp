// Game.cpp
#include "Game.h"
#include "Colors.cpp"
#include <cmath>
#include <iostream>
#include <algorithm>

// Utility: Euclidean distance between two points.
float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

Game::Game() : window(sf::VideoMode(800, 600), "Hex Tic-Tac-Toe", sf::Style::Close),
               currentPlayer('X'), gameOver(false) {
    // Compute the bounding box of the board using the axial positions.
    auto &cells = board.getCells();
    float minX = 1e9, maxX = -1e9, minY = 1e9, maxY = -1e9;
    for (const auto &cell : cells) {
        sf::Vector2f pos = board.axialToPixel(cell.q, cell.r);
        minX = std::min(minX, pos.x);
        maxX = std::max(maxX, pos.x);
        minY = std::min(minY, pos.y);
        maxY = std::max(maxY, pos.y);
    }
    boardWidth = maxX - minX + HEX_SIZE * 2;
    boardHeight = maxY - minY + HEX_SIZE * 2;
    boardOffset = sf::Vector2f((window.getSize().x - boardWidth) / 2 - minX + HEX_SIZE,
                               (window.getSize().y - boardHeight) / 2 - minY + HEX_SIZE);
}

void Game::handleClick(int x, int y) {
    if (gameOver)
        return;
    sf::Vector2f clickPos(x, y);
    // Adjust click position relative to board coordinate system.
    clickPos -= boardOffset;
    
    // Iterate through all cells to see if the click is within a threshold of a cell’s center.
    for (const auto &cell : board.getCells()) {
        sf::Vector2f cellPos = board.axialToPixel(cell.q, cell.r);
        if (distance(clickPos, cellPos) < HEX_SIZE * 0.8f) {  // threshold for click detection
            if (board.makeMove(cell.q, cell.r, currentPlayer)) {
                std::cout << "Debug: Move - Player " << currentPlayer 
                          << " moved to cell (" << cell.q << "," << cell.r << ")\n";
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
            return; // Process only one cell per click.
        }
    }
}

void Game::draw() {
    window.clear(sf::Color::Black);
    board.draw(window, boardOffset);
    // Position UI text outside the board:
    // Place the current turn text above the board (using half of the top margin).
    int topTextY = static_cast<int>(boardOffset.y / 2);
    // Place the winner/draw text below the board.
    int bottomTextY = static_cast<int>(boardOffset.y + boardHeight + (window.getSize().y - (boardOffset.y + boardHeight)) / 2);
    
    // Use the current player's color for the turn text.
    sf::Color turnColor = (currentPlayer == 'X') ? AMU_RED : AMU_GREEN;
    UI::drawText(window, "Player Turn: " + std::string(1, currentPlayer), window.getSize().x / 2, topTextY, 24, turnColor);
    if (gameOver) {
        UI::drawText(window, winnerText, window.getSize().x / 2, bottomTextY, 30, AMU_GREEN);
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
