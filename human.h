//
//  human.h
//  tictactoe
//
//  Created by Jack McNamara on 27/08/2014.
//  Copyright (c) 2014 Jack McNamara. All rights reserved.
//

#ifndef __tictactoe__human__
#define __tictactoe__human__

#include <iostream>
#include "player.h"

class Human : public Player {

public:
    Human(std::string name) : Player(name) {}
    virtual int get_move(const Board *board_state);
    
};

#endif /* defined(__tictactoe__human__) */
