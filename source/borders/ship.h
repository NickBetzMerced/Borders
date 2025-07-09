#ifndef BORDERS_SHIP_H
#define BORDERS_SHIP_H

#include "../engine/engine.h"
#include "item.h"
#include "ship_parts.h"
#include "person.h"

struct Ship : engine::GameObject {
	enum TYPES {SHUTTLE, TOTAL_NUMBER_OF_SHIPS};

	static std::array<std::string, TOTAL_NUMBER_OF_SHIPS> names;
	static std::array<float, TOTAL_NUMBER_OF_SHIPS> frame_masses;
	static std::array<float, TOTAL_NUMBER_OF_SHIPS> turn_rates;

	Ship(int type);

	int type;

	Person* owner;
	std::vector<Person> crew;

	std::string name;
	float turn_rate;
    float speed;
    float acceleration;

	float frame_mass;
	float mass;
	std::vector<ShipPart> parts;

	long double power_draw;

	float fuel_consumption;
	Item* fuel_ptr;
	std::vector<Item> inventory;
};

#endif