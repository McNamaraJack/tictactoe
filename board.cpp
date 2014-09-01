#include <iostream>
#include "board.h"

Board::Board () {
    reset();
}

Board::Board(const Board &board) {
	this->turn = board.turn;
	for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
			this->board_state[i][j] = board.board_state[i][j];
        }
    }
}

void Board::reset () {
    turn = true;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
	        board_state[i][j] = 0;
        }
    }
}

void Board::display () {
    std::cout << std::endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
	        std::cout << " ";
            switch (board_state[i][j]) {
            case 1:
	            std::cout << "X";
                break;
            case -1:
	            std::cout << "O";
                break;
            case 0:
	            std::cout << (char)((int)'1' + (3 * i + j));
                break;
            }
	        std::cout << " ";
            if (j < 2) std::cout << "|";
            else std::cout << std::endl;
        }
	    if (i < 2) {
            std::cout << "---|---|---" << std::endl;
        }
    }
}

bool Board::current_turn() {
    return turn;
}

bool Board::play_move(int move) {
    int i = move / 3;
    int j = move % 3;
    if (board_state[i][j] == 0) {
	    board_state[i][j] = turn ? 1 : -1;
        turn = !turn;
        return true;
    }
    return false;
}

char Board::check_game() {
	int count[9] = { 0 };
    for (int i = 0; i < 8; i++) count[i] = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // Count horizontal and vertical
            count[j] += board_state[i][j];
            count[j + 3] += board_state[j][i];
            // Count total
            count[8] += std::abs((int)board_state[i][j]);
        }
        // Count diagonals
        count[6] += board_state[i][i];
        count[7] += board_state[i][2 - i];
    }
    // Check for wins
    for (int i = 0; i < 8; i++) {
        if (count[i] == 3) return 'X';
        if (count[i] == -3) return 'O';
    }
    // Check for draw
    if (count[8] == 9) return 'D';
	return 0;
}

int Board::get_valid_moves(std::vector<int> *valid_moves) const {
	int move = 0; 
    int count = 0;
	for (int i = 0; i<3; ++i) {
		for (int j = 0; j<3; ++j) {
			if (board_state[i][j] == 0) {
                valid_moves->push_back(move);
                count++;
            }
			move++;
		}
	}
	return count;
}
