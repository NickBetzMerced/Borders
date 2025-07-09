#ifndef BORDERS_TECHNOLOGY_H
#define BORDERS_TECHNOLOGY_H

#include <string>


struct Technology {
	enum TYPES {
	FISSION_REACTOR, FUSION_REACTOR, ANTIMATTER_REACTOR,
	FISSION_ENGINE, FUSION_ENGINE, ANTIMATTER_ENGINE,
	QUANTUM_COMPUTING, OPTICAL_COMPUTING,
	RAILGUN_WEAPONS, LASER_WEAPONS, PLASMA_WEAPONS, 
	FISSION_WARHEADS, FUSION_WARHEADS, ANTIMATTER_WARHEADS,
	LASER_DRILL, LASER_DRILL_2,
	TRANSPORTER, MATTER_SYNTHESIZER,
	NUMBER_OF_TECHNOLOGIES};

	static std::array<std::string, NUMBER_OF_TECHNOLOGIES> names;
	static std::array<std::string, NUMBER_OF_TECHNOLOGIES> descriptions;
	static std::array<char, NUMBER_OF_TECHNOLOGIES> requirements;

	int type;
	int remaining_cost;
	char previous_technology_required;
	Technology(int type);
};

#endif