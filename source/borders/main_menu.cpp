#ifndef MAIN_MENU_CPP
#define MAIN_MENU_CPP

#include "main_menu.h"

MainMenu::MainMenu() : engine::GameObject::GameObject() {
    visible = true;
    back_button = nullptr;
    play_button = Button::makeButton(800, 350, 160, 40, std::string("PLAY"), Button::TYPES::PLAY);
    settings_button = Button::makeButton(800, 450, 160, 40, std::string("SETTINGS"), Button::TYPES::SETTINGS);
    
    update = [this]() {
        if (engine::room == borders::ROOMS::SETTINGS) {
            text = "Ambience volume: ";
            text += "\nSFX volume: ";
            text += "\n\nResolution: ";
            text += "\nFullscreen: ";
        }

        if (play_button && play_button->clicked) {
            std::cout << "GOING TO GAME" << std::endl;
            engine::room = borders::ROOMS::CHARACTER_CREATOR;
            engine::change_room = true;

            play_button->should_close = true;
            settings_button->should_close = true;
            play_button = nullptr;
            settings_button = nullptr;
        }
        if (settings_button && settings_button->clicked) {
            std::cout << "OPENING SETTINGS" << std::endl;
            engine::room = borders::ROOMS::SETTINGS;
            engine::change_room = true;

            play_button->should_close = true;
            settings_button->should_close = true;
            play_button = nullptr;
            settings_button = nullptr;

            back_button = Button::makeButton(1400, 700, 160, 40, std::string("BACK"), Button::TYPES::BACK);
        }
        if (back_button && back_button->clicked) {
            engine::room = borders::ROOMS::MAIN_MENU;
            engine::change_room = true;

            back_button->should_close = true;
            back_button = nullptr;

            play_button = Button::makeButton(800, 350, 160, 40, std::string("PLAY"), Button::TYPES::PLAY);
            settings_button = Button::makeButton(800, 450, 160, 40, std::string("SETTINGS"), Button::TYPES::SETTINGS);
        }
    };

    drawGUI = [this]() {
        if (engine::room == borders::ROOMS::SETTINGS) {
            DrawTextEx(engine::body_font, text.c_str(), Vector2(50, 50), engine::m_font, engine::spacing, WHITE);
        }
    };
}

void MainMenu::makeMainMenu() {
    engine::GameObject::objects.push_back(std::move(std::make_unique<MainMenu>()));
}

#endif