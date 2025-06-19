#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../engine/button.cpp"
#include "borders.cpp"

struct MainMenu : engine::GameObject {
    Button* play_button;
    Button* settings_button;
    Button* back_button;

    std::string text;

    MainMenu();
    static void makeMainMenu();
    
};

#endif