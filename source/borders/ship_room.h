#ifndef BORDERS_SHIP_ROOM_H
#define BORDERS_SHIP_ROOM_H

#include <string>
#include <unordered_map>

struct ShipRoom {
	enum TYPES {RESEARCH_BAY, CCQ_TRAINING_FACILITY, SMALL_CARGO_BAY, MEDIUM_CARGO_BAY, LARGE_CARGO_BAY};
	
	static std::unordered_map<int, std::string> names;
	std::string name;
	int type;
	ShipRoom(int type);
};

#endif