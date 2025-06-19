#ifndef BUTTON_H
#define BUTTON_H

#include "engine.h"

struct Button : engine::GameObject {
    enum TYPES {PLAY, SETTINGS, BACK, EXIT, APPLY_SETTINGS, TRUE, FALSE};
    int width;
    int height;
    int type;

    Rectangle rec;
    bool clicked;

    Color text_color;
    Color box_color;

    std::string title;
    Vector2 text_dimension;
    Button();
    Button(int x, int y, int width, int height, std::string title, int type);
    static Button* makeButton(int x, int y, int width, int height, std::string title, int type);

    std::function<void()> onClick;
};

#endif