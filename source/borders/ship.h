#ifndef BORDERS_SHIP_H
#define BORDERS_SHIP_H

#include "../engine/engine.h"
#include "item.h"
#include "ship_parts.h"
#include "person.h"

struct Ship : engine::GameObject {
	enum TYPES {SHUTTLE, TOTAL_NUMBER_OF_SHIPS};

	static std::array<int, TOTAL_NUMBER_OF_SHIPS> names;
	static std::array<float, TOTAL_NUMBER_OF_SHIPS> turn_rates;
	static std::array<float, TOTAL_NUMBER_OF_SHIPS> speeds;
	static std::array<float, TOTAL_NUMBER_OF_SHIPS> accelerations;

	Person* owner;
	std::string name;
	float turn_rate;
    float speed;
    float acceleration;

	float fuel_consumption;
	std::vector<Item> inventory;
	std::vector<ShipPart> parts; 
};

#endif