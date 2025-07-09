#ifndef ITEM_CPP
#define ITEM_CPP

#include "item.h"
#include <iostream>

/*
Volume is measured in cubic meters, mass in kilograms
*/

std::array<float, Item::NUMBER_OF_ITEMS> Item::densities = {
	70.85, 
	19050
};
std::array<bool, Item::NUMBER_OF_ITEMS> Item::countabilities = {
	false,
	false
};

std::array<float, Item::NUMBER_OF_ITEMS> Item::volumes;

std::array<std::string, Item::NUMBER_OF_ITEMS> Item::names = {
	"Hydrogen",
	"Uranium-235"
};

void Item::updateDimensions() {
	if (countable) {
		volume = item_volume * quantity;
		mass = density * volume;
	}
	else {
		volume = mass / density;
	}
}

Item::Item(int type, float mass) {
	this->mass = mass;
	this->type = type;
	name = Item::names[type];
	countable = Item::countabilities[type];

	density = Item::densities[type];
	updateDimensions();

	quantity = -1;
	item_volume = -1;
}

Item::Item(int type, unsigned int quantity) {
	this->type = type;
	name = Item::names[type];
	countable = Item::countabilities[type];

	if (!countable) {
		std::cout << "WARNING: TRIED TO CREATE AN UNCOUNTABLE ITEM WITH A QUANTITY" << std::endl;
	}
	else {
		this->quantity = quantity;
		density = Item::densities[type];
		item_volume = Item::volumes[type];

		updateDimensions();
	}
}

void Item::consume(float amount) {
	if (mass - amount >= 0) {
		mass -= amount;
		updateDimensions();
	}
	else {
		
	}
};

void Item::consumeQuantity(unsigned int quantity) {
	if (this->quantity - quantity >= 0) {
		this->quantity -= quantity;
		updateDimensions();
	}
	else {
		
	}
};

void Item::add(float amount) {
	this->mass += amount;
}

void Item::addQuantity(unsigned int quantity) {
	this->quantity += quantity;
}

float Item::getMass() {
	return mass;
}

float Item::getVolume() {
	return volume;
}

unsigned int Item::getQuantity() {
	return quantity;
}

bool Item::isCountable() {
	return countable;
}

std::string Item::getName() {
	return name;
}

#endif