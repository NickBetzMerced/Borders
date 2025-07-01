#ifndef BUTTON_H
#define BUTTON_H

#include "engine.h"

struct Button : engine::GameObject {
    enum TYPES {PLAY, SETTINGS, BACK, EXIT, APPLY_SETTINGS, TRUE, FALSE, RESOLUTION};
	
    int width;
    int height;

    Rectangle rec;
    bool clicked;

    Color text_color;
    Color box_color;

    std::string title;
    Vector2 text_dimension;
    Button();
    Button(int x, int y, int width, int height, std::string title);
    static Button* makeButton(int x, int y, int width, int height, std::string title);

    std::function<void()> onClick;
};

#endif