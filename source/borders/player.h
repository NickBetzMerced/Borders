#ifndef PLAYER_H
#define PLAYER_H

#include "../engine/engine.h"
#include "../engine/window.h"

struct Player : engine::GameObject {
    float turnRate;
    float speed;
    float acceleration;

	float fuel;
	float fuel_consumption;

	Window* inventory_window;

    std::string hud_text;
    Player();
    static void makePlayer();
};


#endif