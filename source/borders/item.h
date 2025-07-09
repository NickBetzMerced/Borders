#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <array>

/*
Volume is measured in cubic meters, mass in kilograms

12,000,000 kWh usable per kg of uranium
3kW per person for life support
72 kWh per person per day (15 seconds), or 4.8 kWh per person per second
*/

struct Item {
	enum TYPES {HYDROGEN, URANIUM,
	NUMBER_OF_ITEMS};
	int type;

	private:
	float density;
	static std::array<float, NUMBER_OF_ITEMS> densities;
	static std::array<float, NUMBER_OF_ITEMS> volumes;
	float item_volume;
	float volume;
	float mass;

	static std::array<std::string, NUMBER_OF_ITEMS> names;
	std::string name;

	static std::array<bool, NUMBER_OF_ITEMS> countabilities;
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