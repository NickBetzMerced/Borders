#ifndef BUTTON_H
#define BUTTON_H

#include "engine.cpp"

struct Button : engine::GameObject {
    int width;
    int height;

    Rectangle rec;

    Color text_color;
    Color box_color;

    std::string title;
    Vector2 text_dimension;
    Button();
    Button(int x, int y, int width, int height, std::string title);
    static void makeButton(int x, int y, int width, int height, std::string title);

    std::function<void()> onClick;
};

#endif