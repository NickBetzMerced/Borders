#ifndef PLAYER_H
#define PLAYER_H

#include "../engine/engine.cpp"

struct Player : engine::GameObject {
    float turnRate;
    float speed;
    float acceleration;
    std::string hud_text;
    Player();
    static void makePlayer();
};


#endif