#ifndef BORDERS_SHIP_CPP
#define BORDERS_SHIP_CPP

#include "ship.h"

std::array<std::string, Ship::TOTAL_NUMBER_OF_SHIPS> Ship::names = {
	"Shuttle"
};

std::array<float, Ship::TOTAL_NUMBER_OF_SHIPS> Ship::frame_masses = {
	134000
};

std::array<float, Ship::TOTAL_NUMBER_OF_SHIPS> Ship::turn_rates = {
	80.0
};

Ship::Ship(int type) {
	this->type = type;
	name = Ship::names[type];
	frame_mass = Ship::frame_masses[type];
}

#endif