#ifndef BUTTON_CPP
#define BUTTON_CPP

#include "button.h"

Button::Button(int x, int y, int width, int height, std::string title) : engine::GameObject::GameObject() {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->title = title;
    

    visible = true;

    drawGUI = [this]() {
        DrawRectangle(this->x - (this->width / 2), this->y - (this->height / 2), this->width, this->height, WHITE);
        DrawTextEx(engine::title_font, this->title.c_str(), Vector2(this->x - (this->width / 2), this->y - (this->height / 2)), engine::m_font, engine::spacing, BLACK);
    };
}

void Button::makeButton(int x, int y, int width, int height, std::string title) {
    engine::GameObject::objects.push_back(std::move(std::make_unique<Button>(x, y, width, height, title)));
}

#endif