#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../engine/button.cpp"

struct MainMenu : engine::GameObject {
    MainMenu();
    static void makeMainMenu();
};

#endif