#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
private:
	bool turn;
	char board_state[3][3];

public:
	Board();
	Board(const Board &board);
	void reset();
	void display();
	bool current_turn();
	bool play_move(int move);
	char check_game();
	int get_valid_moves(std::vector<int> *valid_moves) const;
};

#endif
