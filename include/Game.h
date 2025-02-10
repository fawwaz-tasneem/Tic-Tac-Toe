// --- Game.h ---
#ifndef GAME_H
#define GAME_H

#include "HexBoard.h"
#include "UI.h"

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
    void handleClick(int x, int y);
    void draw();
};

#endif
