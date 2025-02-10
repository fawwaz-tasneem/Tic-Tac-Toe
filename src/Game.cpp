// Game.cpp
#include "Game.h"
#include "Colors.cpp"
#include <cmath>
#include <iostream>
#include <algorithm>

// Utility function: Euclidean distance between two points.
float distance(const sf::Vector2f& a, const sf::Vector2f& b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

Game::Game() 
    : window(sf::VideoMode::getDesktopMode(), "Hex Tic Tac Toe", sf::Style::Fullscreen),
      currentPlayer('X'),
      gameOver(false),
      bgColor(sf::Color::Black) {
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
    
    recalcBoardOffset();
    // Clocks (animationClock and gameClock) start automatically.
}


void Game::recalcBoardOffset() {
    // Define larger margins so that UI text is well separated from the board.
    int topMargin = 200;
    int bottomMargin = 200;
    float availableHeight = window.getSize().y - topMargin - bottomMargin;
    
    // Recalculate the board bounding box in case the window size changed.
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
    
    boardOffset = sf::Vector2f(
        (window.getSize().x - boardWidth) / 2 - minX + HEX_SIZE,
        topMargin + (availableHeight - boardHeight) / 2 - minY + HEX_SIZE
    );
}

void Game::handleClick(int x, int y) {
    if (gameOver)
        return;
    sf::Vector2f clickPos(x, y);
    // Adjust click position relative to board coordinate system.
    clickPos -= boardOffset;
    
    // Iterate through all cells to see if the click is near a cell’s center.
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
    window.clear(bgColor);
    
    board.draw(window, boardOffset);
    
    // Draw a title at the very top.
    UI::drawText(window, "Hex Tic Tac Toe", window.getSize().x / 2, 30, 42, sf::Color::Cyan);
    
    // Draw current turn text near the top (outside the board area).
    sf::Color turnColor = (currentPlayer == 'X') ? AMU_RED : AMU_GREEN;
    UI::drawText(window, "Player Turn: " + std::string(1, currentPlayer),
                 window.getSize().x / 2, 80, 36, turnColor);
    
    // Draw timer panel in the top-right.
    float elapsed = gameClock.getElapsedTime().asSeconds();
    int secondsElapsed = static_cast<int>(elapsed);
    std::string timerStr = "Time: " + std::to_string(secondsElapsed) + " sec";
    
    // Draw a semi-transparent panel behind the timer text.
    sf::RectangleShape timerPanel;
    timerPanel.setSize(sf::Vector2f(200, 50));
    timerPanel.setFillColor(sf::Color(0, 0, 0, 150)); // semi-transparent black
    timerPanel.setPosition(window.getSize().x - 220, 10);
    window.draw(timerPanel);
    
    UI::drawText(window, timerStr, window.getSize().x - 120, 35, 28, sf::Color::White);
    
    // Draw restart and background toggle prompts.
    if (gameOver) {
        float elapsedAnim = animationClock.getElapsedTime().asSeconds();
        float scale = 1.0f + 0.2f * std::sin(2 * 3.1415f * elapsedAnim); // Pulsate effect
        
        // Determine winner color: if "Player X", use AMU_RED; if "Player O", use AMU_GREEN; else white.
        sf::Color winColor;
        if (winnerText.find("Player X") != std::string::npos)
            winColor = AMU_RED;
        else if (winnerText.find("Player O") != std::string::npos)
            winColor = AMU_GREEN;
        else
            winColor = sf::Color::White;
            
        UI::drawWinnerText(window, winnerText,
                           window.getSize().x / 2, window.getSize().y - 60, 48, winColor, scale);
        
        UI::drawText(window, "Press R to Restart | Press B to Toggle Background", window.getSize().x / 2, window.getSize().y - 20, 28, sf::Color::Yellow);
    } else {
        UI::drawText(window, "Click a hexagon to play | Press B to Toggle Background", window.getSize().x / 2, window.getSize().y - 30, 28, sf::Color::Yellow);
    }
    
    // Draw your signature at the bottom-right in small text.
    UI::drawText(window, "Fawwaz Bin Tasneem", window.getSize().x - 80, window.getSize().y - 25, 18, sf::Color::White);
    
    window.display();
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::KeyPressed) {
                // Reset game if R is pressed.
                if (event.key.code == sf::Keyboard::R) {
                    board = HexBoard();
                    currentPlayer = 'X';
                    gameOver = false;
                    winnerText = "";
                    animationClock.restart();
                    gameClock.restart();
                    std::cout << "Debug: Game reset." << std::endl;
                }
                // Toggle background color if B is pressed.
                else if (event.key.code == sf::Keyboard::B) {
                    if (bgColor == sf::Color::Black) {
                        bgColor = sf::Color::White;
                        std::cout << "Debug: Background changed to White." << std::endl;
                    } else {
                        bgColor = sf::Color::Black;
                        std::cout << "Debug: Background changed to Black." << std::endl;
                    }
                }
            }
            else if (event.type == sf::Event::Resized) {
                // Update the view to the new size.
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
                recalcBoardOffset();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                handleClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
        draw();
    }
}
