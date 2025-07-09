#ifndef BORDERS_PERSON_H
#define BORDERS_PERSON_H

#include <string>
#include <vector>

struct Ship;

struct Faction;

struct Skill {
	enum {PILOTING, CCQ, ENGINEERING, MEDICAL, INTELLECTUAL, CRAFTING, NAVIGATION, NUMBER_OF_SKILLS};
};

struct Proficiency {
	
};

struct Person {
	std::string name;
	long int money;

	Faction* faction;

	std::vector<Ship*> ships_owned;
	Ship* current_ship;
};

#endif