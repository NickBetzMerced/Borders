#ifndef PLAYER_H
#define PLAYER_H

#include "../engine/engine.cpp"

struct Player : engine::GameObject {
    float turnRate;
    Player();
    static void makePlayer();
};


#endif