#ifndef BORDERS_SHIP_PARTS_CPP
#define BORDERS_SHIP_PARTS_CPP

#include "ship_parts.h"

std::array<std::string, ShipPart::NUMBER_OF_SHIP_PARTS> ShipPart::names = {
	"Gas Core Fision Engine",
	"Fusion Engine",
	"Antimatter Engine",
	
	"Research Bay",
	"CCQ Training Facility",

	"Small Cargo Bay",
	"Medium Cargo Bay",
	"Large Cargo Bay",

	"Small Manufacturing Bay",
	"Medium Manufacturing Bay",

	"Small Onboard Farm",

	"Simple Living Quarters",
	"Fine Living Quarters",
	"Luxurious Living Quarters",

	"Simple Dorm",
	"Fine Dorm",
	"Luxurious Dorm"
};

std::array<float, ShipPart::NUMBER_OF_SHIP_PARTS> ShipPart::masses = {
	20000,
	50000,
	100000,

	8000,
	5000,

	4000,
	40000,
	400000,
	
	50000,
	100000,

	4500,

	1000,
	1800,
	3500,

	2000,
	2800,
	4500
};

ShipPart::ShipPart(int type) {
	this->type = type;
	name = ShipPart::names[type];
	mass = ShipPart::masses[type];
}

#endif