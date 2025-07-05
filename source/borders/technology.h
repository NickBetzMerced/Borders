#ifndef BORDERS_TECHNOLOGY_H
#define BORDERS_TECHNOLOGY_H

#include <string>
#include <unordered_map>

struct Technology {
	enum TYPES {FISSION_ENGINE, FUSION_ENGINE, ANTIMATTER_ENGINE,
	QUANTUM_COMPUTING,
	RAILGUN_WEAPONS, LASER_WEAPONS, PLASMA_WEAPONS, 
	FISSION_WARHEADS, FUSION_WARHEADS, ANTIMATTER_WARHEADS};
	static std::unordered_map<int, std::string> names;
	static std::unordered_map<int, std::string> descriptions;
	
	int type;
	Technology(int type);
};

#endif