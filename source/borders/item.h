#ifndef ITEM_H
#define ITEM_H

#include <unordered_map>
#include <string>

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
	float item_volume;
	float volume;
	float mass;

	static std::unordered_map<int, std::string> names;
	std::string name;

	static std::unordered_map<int, bool> countabilities;
	bool countable;
	int quantity;

	void updateDimensions();

	public:
	Item(int type, float mass);
	Item(int type, unsigned int quantity);

	void consume(float amount);
	void consumeQuantity(unsigned int quantity);

	void add(float amount);
	void addQuantity(unsigned int quantity);

	float getMass();
	float getVolume();
	unsigned int getQuantity();
	bool isCountable();
	std::string getName();
};

#endif