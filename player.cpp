#include <string>

#include "player.h"

Player::Player (std::string name) {
    this->name = name;
}

std::string Player::get_name() {
	return name;
}
