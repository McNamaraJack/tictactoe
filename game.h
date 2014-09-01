#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "human.h"
#include "ai.h"

class Game {
private:
    Board *board;
	Player *playerX, *playerO;

public:
	Game();
    void run();
    void welcome_message();
    void declare_winner(char winner);
    bool player_select();
};

#endif