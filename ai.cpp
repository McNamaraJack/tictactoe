#include <iostream>
#include <chrono>
#include <random>
#include "ai.h"

AI::AI(std::string name, char id, DifficultyLevel difficulty) : Player(name) {
    identity = id;
    Difficulty = difficulty;
}

// Checks to see if a winning/losing move will occur before the next turn
// input: 	board_state - copy of current board_state
// 		move - position in board
//		player - current player 'X' or 'O'
// returns: 	1 - winning move
//		-1 - losing move
//		0 - drawing move
int AI::check_next_move(Board board_state, int move, char player) {
    Board next_board_state(board_state);
    next_board_state.play_move(move);
    if (next_board_state.check_game() == player) return 1;
    else if (next_board_state.check_game() == 'D') return 0;
    else return -1;
}

// Computes the best possible move to take by examining all possible scenarios (recursive minimax function)
// input: 	board_state - copy of current board_state
// 		move - position in board
//		player - current player 'X' or 'O'
// returns: 	1 - winning move
// 		-1 - losing move
// 		0 - drawing move
int AI::rank_move(Board board_state, int m, char player) {
	board_state.play_move(m);
	
	char check = board_state.check_game();	
	if (check != 0) {
		if (check == this->identity) return 1;
		if (check == 'D') return 0;
		return -1;
	}

	char next_player = (player == 'O') ? 'X' : 'O';
	std::vector<int> moves;
    int size = board_state.get_valid_moves(&moves);

	if(player == this->identity) {
		int bestVal = 1;
		for (int idx = 0; idx < size; ++idx) {
			int val = rank_move(board_state, moves[idx], next_player);
			bestVal = std::min(bestVal, val);
		}
		return bestVal;
	}
	else {
		int bestVal = -1;
		for (int idx = 0; idx < size; ++idx) {
			int val = rank_move(board_state, moves[idx], next_player);
			bestVal = std::max(bestVal, val);
		}
		return bestVal;
	}
}

int AI::get_move(const Board *board_state) {
	std::vector<int> moves;
    int size = board_state->get_valid_moves(&moves);
	unsigned seed = ((unsigned)std::chrono::system_clock::now().time_since_epoch().count());
    std::default_random_engine generator (seed);
	
	switch (Difficulty) {
	case AI::Easy:
		{
			std::uniform_int_distribution<int> distribution(0,size);
			return moves[distribution(generator)]; // random move
		}
		break;		
	case AI::Hard:
        	{
			// Takes a winning move, or a move that doesn't result in a loss before the next turn
			
			// ==================================================================//			
			// TODO - Implement Hard AI
			// ==================================================================//
                
            std::uniform_int_distribution<int> distribution(0,size);
                for (int i = 0; i < size; i++) {
                    int move = moves[i];
                    if (check_next_move(*board_state, move, this->identity) == 1) {
                        return move;
                    }
                }
                for (int i = 0; i < size; i++) {
                    int move = moves[i];
                    if (check_next_move(*board_state, move, this->identity) == 0) {
                        return move;
                    }
                }
                return moves[0];
		}
		break;
	case AI::Impossible:
		{
			int best_rank = -1;
			int move_idx = 0;
			for (int idx = 0; idx < size; ++idx) {
		        Board board_copy(*board_state);
				int cur_rank = rank_move(board_copy, moves[idx], this->identity);
				if (cur_rank > best_rank) {
					move_idx = idx;
					best_rank = cur_rank;
				}
			}
			return moves[move_idx]; // Perfect Play
		}
		break;
	default:
		break;
	}
}
