#ifndef PLAYER_H
#define PLAYER_H

#include "../engine/engine.h"
#include "../engine/window.h"

struct Item;

struct InventoryWindow;

struct Player : engine::GameObject {
	static Player* player_ptr;
    float turnRate;
    float speed;
    float acceleration;

	float fuel;
	Item* fuel_ptr;
	float fuel_consumption;

	std::vector<Item> inventory;
	InventoryWindow* inventory_window;

    std::string hud_text;
    Player();
    static void makePlayer();
};


#endif