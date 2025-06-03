#ifndef WINDOW_H
#define WINDOW_H

#include "engine.cpp"

struct Window : engine::GameObject {
    enum TYPES {CHARACTER_CREATOR};
    static const std::array<std::string, 1> TITLES;
    int type;

    std::string title;
    bool resizable;
    
    Window();
    Window(int type);

    static void makeWindow(int type);
};

#endif