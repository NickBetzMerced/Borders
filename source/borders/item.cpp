#ifndef ITEM_CPP
#define ITEM_CPP

#include "item.h"
#include <iostream>

/*
Volume is measured in cubic meters, mass in kilograms
*/

std::unordered_map<int, float> Item::densities = {
	{Item::TYPES::FUEL, 70.85}
};
std::unordered_map<int, bool> Item::countabilities = {
	{Item::TYPES::FUEL, false}	
};

std::unordered_map<int, float> Item::volumes;

Item::Item(int type, float mass) {
	this->mass = mass;
	this->type = type;

	density = Item::densities[type];
	volume = mass / density;
	quantity = -1;
}

Item::Item(int type, unsigned int quantity) {
	this->type = type;
	if (!Item::countabilities[type]) {
		std::cout << "WARNING: TRIED TO CREATE AN UNCOUNTABLE ITEM WITH A QUANTITY" << std::endl;
	}
	else {
		this->quantity = quantity;
		density = Item::densities[type];
		volume = Item::volumes[type] * quantity;
		mass = density * volume;
	}
}

#endif