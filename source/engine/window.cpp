#ifndef WINDOW_CPP
#define WINDOW_CPP

#include "window.h"
#include <algorithm>

#define DEFAULT_FONT_SIZE 20

Window* Window::makeWindow(int type) {
    std::unique_ptr<Window> window = std::make_unique<Window>(type);
    Window* window_ptr = window.get();
    engine::GameObject::objects.push_back(std::move(window));
    return window_ptr;
}

const std::array<std::string, 2> Window::TITLES = {
    "Character Creator",
	"Inventory"
};

Window::Window() {

}

Window::Window(int type) {
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

    drawGUI = [this]() {
        DrawRectangle(x, y, width, height, BLACK);
        DrawRectangleLinesEx(Rectangle(x, y, width, y + 85), 2, WHITE);
        DrawRectangleLinesEx(Rectangle(x, y, width, height), 2, WHITE);
        DrawTextEx(engine::title_font, title.c_str(), Vector2(x + 10, y + 10), engine::l_font, engine::spacing, WHITE);
    };
}

#endif