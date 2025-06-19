#ifndef MAIN_MENU_CPP
#define MAIN_MENU_CPP

#include "main_menu.h"
#include <iostream>

MainMenu::MainMenu() : engine::GameObject::GameObject() {
    visible = true;
    back_button = nullptr;
    apply_settings_button = nullptr;
    toggle_button = nullptr;
    play_button = Button::makeButton(800, 350, 160, 40, std::string("PLAY"), Button::TYPES::PLAY);
    settings_button = Button::makeButton(800, 450, 160, 40, std::string("SETTINGS"), Button::TYPES::SETTINGS);
    exit_button = Button::makeButton(800, 550, 160, 40, std::string("EXIT"), Button::TYPES::EXIT);
    
    update = [this]() {
        if (engine::room == borders::ROOMS::SETTINGS) {
            text = "Ambience volume: ";
            text += "\n\nSFX volume: ";
            text += "\n\n\n\nResolution: ";
            text += "\n\nFullscreen: ";
        }

        if (play_button && play_button->clicked) {
            std::cout << "GOING TO GAME" << std::endl;
            engine::room = borders::ROOMS::CHARACTER_CREATOR;
            engine::change_room = true;

            play_button->should_close = true;
            settings_button->should_close = true;
            exit_button->should_close = true;
            play_button = nullptr;
            settings_button = nullptr;
            exit_button = nullptr;
        }
        if (settings_button && settings_button->clicked) {
            std::cout << "OPENING SETTINGS" << std::endl;
            engine::room = borders::ROOMS::SETTINGS;
            engine::change_room = true;

            play_button->should_close = true;
            settings_button->should_close = true;
            exit_button->should_close = true;
            play_button = nullptr;
            settings_button = nullptr;
            exit_button = nullptr;

            back_button = Button::makeButton(1400, 700, 160, 40, std::string("BACK"), Button::TYPES::BACK);
            apply_settings_button = Button::makeButton(1100, 700, 280, 40, std::string("APPLY SETTINGS"), Button::TYPES::APPLY_SETTINGS);
            toggle_button = Button::makeButton(210, 310, 160, 40, std::string("FALSE"), Button::TYPES::FALSE);
        }
        if (toggle_button && toggle_button->clicked) {
            if (engine::fullscreen) {
                toggle_button->should_close = true;
                toggle_button = Button::makeButton(210, 310, 160, 40, std::string("FALSE"), Button::TYPES::FALSE);
                engine::fullscreen = false;
            }
            else {
                toggle_button->should_close = true;
                toggle_button = Button::makeButton(210, 310, 160, 40, std::string("TRUE"), Button::TYPES::TRUE);
                engine::fullscreen = true;
            }
        }
        if (back_button && back_button->clicked) {
            engine::room = borders::ROOMS::MAIN_MENU;
            engine::change_room = true;

            back_button->should_close = true;
            back_button = nullptr;
            apply_settings_button->should_close = true;
            apply_settings_button = nullptr;
            toggle_button->should_close = true;
            toggle_button = nullptr;

            play_button = Button::makeButton(800, 350, 160, 40, std::string("PLAY"), Button::TYPES::PLAY);
            settings_button = Button::makeButton(800, 450, 160, 40, std::string("SETTINGS"), Button::TYPES::SETTINGS);
            exit_button = Button::makeButton(800, 550, 160, 40, std::string("EXIT"), Button::TYPES::EXIT);
        }
        if (exit_button && exit_button->clicked) {
            engine::exit = true;
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