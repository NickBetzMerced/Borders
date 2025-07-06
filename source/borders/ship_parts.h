#ifndef BORDERS_SHIP_PARTS_H
#define BORDERS_SHIP_PARTS_H

#include <string>
#include <unordered_map>

struct ShipPart {
	enum TYPES {RESEARCH_BAY, 
		CCQ_TRAINING_FACILITY, 
		SMALL_CARGO_BAY, MEDIUM_CARGO_BAY, LARGE_CARGO_BAY, MANUFACTURING_BAY,
		ONBOARD_FARM};
	
	static std::unordered_map<int, std::string> names;
	std::string name;
	int type;
	ShipPart(int type);
};

#endif