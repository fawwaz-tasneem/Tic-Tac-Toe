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
    sf::Vector2f boardOffset; // Offset to center the board in the window
    float boardWidth;         // Width of the board’s bounding box
    float boardHeight;        // Height of the board’s bounding box
    void handleClick(int x, int y);
    void draw();
};

#endif
