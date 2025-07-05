#ifndef BORDERS_SHIP_H
#define BORDERS_SHIP_H

#include "../engine/engine.h"
#include "item.h"
#include "ship_room.h"
#include "person.h"

struct Ship : engine::GameObject {
	enum TYPES {};
	static std::unordered_map<std::string, int> names;
	static std::unordered_map<std::string, float> turn_rates;
	static std::unordered_map<std::string, float> speeds;
	static std::unordered_map<std::string, float> accelerations;

	Person owner;
	std::string name;
	float turn_rate;
    float speed;
    float acceleration;

	float fuel_consumption;
	std::vector<Item> inventory;
	std::vector<ShipRoom> rooms; 
};

#endif