#include <cstdlib>
#include <iostream>
#include <string>
#include <limits>
#include "game.h"

Game::Game() {
    welcome_message();
    board = new Board();
    playerX = NULL;
    playerO = NULL;
}

void Game::run() {
    bool playing = player_select();
    while (playing) {
		board->display();

		char winner = board->check_game();
        if (winner != 0) {
			declare_winner(winner);
            board->reset();
			playing = player_select();
            continue;
		}

        Player *current = board->current_turn() ? playerX : playerO;
		std::cout << "It's " << current->get_name() << "'s move" << std::endl;
        while (1) {
            int move = current->get_move(board);
            bool valid = board->play_move(move);
			if (valid) break;
			std::cout << "That position has been already taken." << std::endl;
		}

        current = NULL;
	}
}

void Game::welcome_message() {
	std::cout << "=======================================================================" << std::endl;
	std::cout << "                    WELCOME TO T3: TOE-TIC-TAC!!!" << std::endl;
	std::cout << "=======================================================================" << std::endl;
}

void Game::declare_winner(char winner) {
    std::cout << "============================" << std::endl;
    switch (winner) {
    case 'X':
		std::cout << "The winner is " << playerX->get_name() << std::endl;
        break;
    case 'O':
		std::cout << "The winner is " << playerO->get_name() << std::endl;
        break;
    case 'D':
		std::cout << "The game is a draw" << std::endl;
        break;
    }
	std::cout << "============================" << std::endl;
}

bool Game::player_select() {
	int option = 0;
	
	std::string prompt("Choose an option:\n");
	prompt += "[1] Begin a new game\n";
	prompt += "[2] Play again\n";
	prompt += "[3] Quit\n?";
	
	while ( (std::cout << prompt) &&
			(!(std::cin >> option) || (option < 1) || (option > 3))){
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
    switch (option) {
    case 1:
        playerX = NULL;
        playerO = NULL;
        break;
    case 2:
        if (playerX == NULL || playerO == NULL) break;
        return true;
    case 3:
        std::cout << "Goodbye." << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	    std::cin.get();
        return false;
	}

    option = 0;
    std::string name("Player 'X'");
    prompt = " is a:\n";
    prompt += "[1] Human\n";
    prompt += "[2] Easy Computer\n";
    prompt += "[3] Hard Computer\n";
    prompt += "[4] Impossible Computer\n?";
    
	while ( (std::cout << name << prompt) &&
			(!(std::cin >> option) || (option < 1) || (option > 4))) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}    
	if(playerX) delete playerX;
    switch (option) {
    case 1:
	    playerX = new Human("Human X");
        break;
    case 2:
		playerX = new AI("Easy X", 'X', AI::DifficultyLevel::Easy);
		break;
    case 3:
		playerX = new AI("Hard X", 'X', AI::DifficultyLevel::Hard);
		break;
    case 4:
		playerX = new AI("Impossible X", 'X', AI::DifficultyLevel::Impossible);
		break;
    }

    option = 0;
    name = "Player 'O'";
    while ( (std::cout << name << prompt) &&
    		(!(std::cin >> option) || (option < 1) || (option > 4))) {
    	std::cin.clear();
    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }    
	if(playerO) delete playerO;
    switch (option) {
    case 1:
	    playerO = new Human("Human O");
        break;
    case 2:
		playerO = new AI("Easy O", 'O', AI::DifficultyLevel::Easy);
		break;
    case 3:
		playerO = new AI("Hard O", 'O', AI::DifficultyLevel::Hard);
		break;
    case 4:
		playerO = new AI("Impossible O", 'O', AI::DifficultyLevel::Impossible);
		break;
    }
    return true;
}
