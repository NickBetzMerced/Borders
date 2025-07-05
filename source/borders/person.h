#ifndef BORDERS_PERSON_H
#define BORDERS_PERSON_H

#include <string>
#include <vector>

struct Ship;

struct Faction;

struct Person {
	std::string name;
	long int money;

	Faction faction;

	std::vector<Ship> ships_owned;
};

#endif