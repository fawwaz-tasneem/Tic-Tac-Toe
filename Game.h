// --- Game.h ---
#ifndef GAME_H
#define GAME_H

#include "HexBoard.h"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window;
    HexBoard board;
    char currentPlayer;
    void handleClick(int x, int y);
    void draw();
};

#endif
