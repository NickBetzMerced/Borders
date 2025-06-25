#ifndef WINDOW_H
#define WINDOW_H

#include "engine.h"

struct Window : engine::GameObject {
    enum TYPES {CHARACTER_CREATOR, INVENTORY};
    static const std::array<std::string, 2> TITLES;
    int type;

    std::string title;
    bool resizable;
    
    Window();
    Window(int type);

    static Window* makeWindow(int type);
};

#endif