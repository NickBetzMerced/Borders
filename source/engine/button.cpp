#ifndef BUTTON_CPP
#define BUTTON_CPP

#include "button.h"

Button::Button(int x, int y, int width, int height, std::string title) : engine::GameObject::GameObject() {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    rec = Rectangle(this->x - (this->width / 2), this->y - (this->height / 2), this->width, this->height);

    this->title = title;
    text_color = WHITE;
    box_color = BLACK;
    text_dimension = MeasureTextEx(engine::title_font, title.c_str(), engine::m_font, engine::spacing);

    visible = true;

    update = [this]() {
        if (engine::l_mouse_clicked && CheckCollisionPointRec(engine::mouse_pos, rec)) {
            if (onClick) {
                onClick();
            }
            should_close = true;
        }
        std::cout << CheckCollisionPointRec(engine::mouse_pos, rec) << std::endl;
        if (text_color.a < 255 && CheckCollisionPointRec(engine::mouse_pos, rec)) {
            text_color.a += 1;
            
        }
        else if (text_color.a > 127 && !CheckCollisionPointRec(engine::mouse_pos, rec)) {
            text_color.a -= 1;
        }
    };

    drawGUI = [this]() {
        DrawRectangle(this->x - (this->width / 2), this->y - (this->height / 2), this->width, this->height, box_color);
        DrawRectangleLinesEx(rec, 2, text_color);
        DrawTextEx(engine::title_font, this->title.c_str(), Vector2(this->x - (text_dimension.x / 2), this->y - (text_dimension.y / 2)), engine::m_font, engine::spacing, text_color);
    };
}

void Button::makeButton(int x, int y, int width, int height, std::string title) {
    engine::GameObject::objects.push_back(std::move(std::make_unique<Button>(x, y, width, height, title)));
}

#endif