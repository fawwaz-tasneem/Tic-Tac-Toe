// Game.h
#ifndef GAME_H
#define GAME_H

#include "HexBoard.h"
#include "UI.h"
#include <SFML/Graphics.hpp>
#include <string>

class Game {
public:
    Game();
    void run();
    
private:
    sf::RenderWindow window;
    HexBoard board;
    char currentPlayer;
    bool gameOver;
    std::string winnerText;
    sf::Vector2f boardOffset; // Offset to center the board in the designated UI area.
    float boardWidth;         // Width of the board’s bounding box.
    float boardHeight;        // Height of the board’s bounding box.
    sf::Color bgColor;        // Background color (toggled with 'B').
    sf::Clock animationClock; // Clock for winner animation.
    sf::Clock gameClock;      // Clock for elapsed game time.
    
    // Recalculate board offset based on the current window size.
    void recalcBoardOffset();
    
    void handleClick(int x, int y);
    void draw();
};

#endif
