#ifndef BORDERS_FACTION_H
#define BORDERS_FACTION_H

#include "ship.h"
#include "technology.h"

struct Faction {
	std::vector<Ship> ships;
	std::vector<Person> people;
	std::vector<Technology> technology;

	static std::vector<Faction> factions;
};

#endif