#ifndef INVENTORY_WINDOW
#define INVENTORY_WINDOW

#include "../engine/window.h"

struct Player;
struct Item;

struct InventoryWindow : Window {
	static bool exists;
	unsigned int page;
	std::string text;
	float total_mass;
	float total_volume;

	InventoryWindow();
	~InventoryWindow();
	static InventoryWindow* makeInventoryWindow();
};

#endif