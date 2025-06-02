#ifndef WINDOW_CPP
#define WINDOW_CPP

#include "window.h"
#include <algorithm>

#define DEFAULT_FONT_SIZE 20

void window::makeWindow(int type) {
    engine::GameObject::objects.push_back(std::move(std::make_unique<window>(type)));
}

const std::array<std::string, 1> window::TITLES = {
    "Character Creator"
};

window::window() {

}

window::window(int type) {
    visible = true;
    x = 0;
    y = 0;
    width = 1280;
    height = 720;
    this->type = type;
    
    resizable = false;

    std::function<void()> b_update;
    b_update = update;
    update = [this, b_update]() {
        b_update();
        title = TITLES[this->type];

        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && resizable) {
            Vector2 mouse = engine::relative_mouse_pos;
            
            int mouse_x_left_difference = abs(mouse.x - x);
            int mouse_x_right_difference = abs(mouse.x - (width + x));
            int mouse_y_up_difference = abs(mouse.y - y);
            int mouse_y_down_difference = abs(mouse.y - (height + y));

            

            bool mouse_touching_horizonal_sides = (mouse_x_left_difference < 10 || mouse_x_right_difference < 10);
            bool mouse_touching_vertical_sides = (mouse_y_up_difference < 10 || mouse_y_down_difference < 10);
            
            if (mouse_touching_horizonal_sides) {
                if (mouse_x_left_difference < mouse_x_right_difference) {
                    int diff = x - mouse.x;
                    x = mouse.x;
                    width = width + diff;
                }
                else if (mouse_x_left_difference > mouse_x_right_difference) {
                    width = mouse.x - x;
                }
            }
            if (mouse_touching_vertical_sides) {
                if (mouse_y_up_difference < mouse_y_down_difference) {
                    int diff = y - mouse.y;
                    y = mouse.y;
                    height = height + diff;
                }
                else if (mouse_y_up_difference > mouse_y_down_difference) {
                    height = mouse.y - y;
                }
            }
        }
    };

    draw = [this]() {
        DrawRectangle(x, y, width, height, WHITE);
        DrawRectangleLinesEx(Rectangle(x, y, width, y + 25), 2, BLACK);
        DrawRectangleLinesEx(Rectangle(x, y, width, height), 2, BLACK);
        DrawTextEx(engine::title_font, title.c_str(), Vector2(x + 5, y + 5), engine::l_font, engine::spacing, BLACK);
    };
}

#endif