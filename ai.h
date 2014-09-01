#ifndef AI_H
#define AI_H

#include "player.h"

class AI : public Player {
public :
	enum DifficultyLevel { Easy, Hard, Impossible };

	virtual int get_move(const Board *board_state);
	int rank_move(Board board_state, int m, char player);
	int check_next_move(Board board_state, int m, char player);
	AI(std::string name, char id, DifficultyLevel difficulty = Easy);

private:
	DifficultyLevel Difficulty;
	char identity;
};

#endif
