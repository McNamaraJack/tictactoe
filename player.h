#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "board.h"

class Player {
private:
	std::string name;

public:
	Player(std::string name);
	std::string get_name();
	virtual int get_move(const Board *board_state) = 0;
};

#endif
