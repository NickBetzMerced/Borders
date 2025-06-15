#ifndef BUTTON_H
#define BUTTON_H

#include "engine.cpp"

struct Button : engine::GameObject {
    int width;
    int height;
    std::string title;
    Button();
    Button(int x, int y, int width, int height, std::string title);
    static void makeButton(int x, int y, int width, int height, std::string title);
};

#endif