#ifndef ITEM_H
#define ITEM_H

#include <unordered_map>

/*
Volume is measured in cubic meters, mass in kilograms
*/

struct Item {
	enum TYPES {FUEL};
	int type;

	private:
	float density;
	static std::unordered_map<int, float> densities;
	static std::unordered_map<int, float> volumes;
	float volume;
	float mass;

	static std::unordered_map<int, bool> countabilities;
	bool countable;
	int quantity;

	public:
	Item(int type, float mass);
	Item(int type, unsigned int quantity);
};

#endif