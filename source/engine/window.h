#ifndef WINDOW_H
#define WINDOW_H

#include "engine.cpp"

struct window : engine::GameObject {
    enum TYPES {WELCOME_WINDOW};
    static const std::array<std::string, 1> TITLES;
    int type;

    std::string title;
    bool resizable;
    
    window();
    window(int type);

    static void makeWindow(int type);
};

#endif