//
//  human.cpp
//  tictactoe
//
//  Created by Jack McNamara on 27/08/2014.
//  Copyright (c) 2014 Jack McNamara. All rights reserved.
//

#include "human.h"

int Human::get_move(const Board *board_state) {
    int option = 0;
    while ((std::cout << "Enter the number to take: " << std::endl) && (!(std::cin >> option) || (option < 1) || (option > 9) )) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return option - 1;
}