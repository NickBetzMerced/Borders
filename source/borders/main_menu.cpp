#ifndef MAIN_MENU_CPP
#define MAIN_MENU_CPP

#include "main_menu.h"

MainMenu::MainMenu() : engine::GameObject::GameObject() {
    Button::makeButton(800, 450, 160, 40, std::string("PLAY"));
    Button::makeButton(800, 550, 160, 40, std::string("SETTINGS"));
    std::cout << "MADE MAIN MENU AND BUTTONS" << std::endl;
}

void MainMenu::makeMainMenu() {
    engine::GameObject::objects.push_back(std::move(std::make_unique<MainMenu>()));
}

#endif