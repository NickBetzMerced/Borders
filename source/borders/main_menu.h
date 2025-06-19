#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../engine/button.h"
#include "borders.h"

struct MainMenu : engine::GameObject {
    Button* play_button;
    Button* settings_button;
    Button* exit_button;

    Button* back_button;
    Button* apply_settings_button;

    Button* toggle_button;

    std::string text;

    MainMenu();
    static void makeMainMenu();
    
};

#endif