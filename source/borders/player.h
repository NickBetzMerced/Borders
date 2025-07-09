#ifndef PLAYER_H
#define PLAYER_H

#include "../engine/window.h"
#include "ship.h"

struct Item;

struct InventoryWindow;

struct Player : Ship {
	static Player* player_ptr;

	InventoryWindow* inventory_window;

    std::string hud_text;
	std::string hud_text_2;
    Player();
    static void makePlayer();
};


#endif