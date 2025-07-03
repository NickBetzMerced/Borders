#ifndef WINDOW_H
#define WINDOW_H

#include "engine.h"

struct Window : engine::GameObject {
    enum TYPES {CHARACTER_CREATOR, INVENTORY, TOTAL_WINDOW_TYPES};
    static const std::array<std::string, TOTAL_WINDOW_TYPES> TITLES;
    int type;

    std::string title;
    bool resizable;
    
    Window();
    Window(int type);

    static Window* makeWindow(int type);
};

#endif