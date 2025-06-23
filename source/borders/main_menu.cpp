#ifndef MAIN_MENU_CPP
#define MAIN_MENU_CPP

#include "main_menu.h"
#include <iostream>

void MainMenu::closeButton(Button*& button) {
	if (button) {
		button->should_close = true;
		button = nullptr;
	}
}

MainMenu::MainMenu() : engine::GameObject::GameObject() {
    visible = true;

    back_button = nullptr;
    apply_settings_button = nullptr;
    toggle_button = nullptr;
	resolution_button = nullptr;

    play_button = Button::makeButton(800, 350, 160, 40, std::string("PLAY"), Button::TYPES::PLAY);
    settings_button = Button::makeButton(800, 450, 160, 40, std::string("SETTINGS"), Button::TYPES::SETTINGS);
    exit_button = Button::makeButton(800, 550, 160, 40, std::string("EXIT"), Button::TYPES::EXIT);

	row_selection = 0;

	onUp = [this]() {
		if (row_selection > 0) {
			row_selection--;
			std::cout << "UP BUTTON PRESSED" << std::endl;
		}
	};
	onDown = [this]() {
		if (row_selection < MainMenu::SETTINS_INDEX_LIMIT) {
			row_selection++;
			std::cout << "DOWN BUTTON PRESSED" << std::endl;
		}
	};
	onLeft = [this]() {
		if (row_selection == FULLSCREEN_INDEX) {
			selected_fullscreen = !selected_fullscreen;
		}
	};
	onRight = [this]() {
		if (row_selection == FULLSCREEN_INDEX) {
			selected_fullscreen = !selected_fullscreen;
		}
	};

	std::function<void()> b_update = update;
    update = [this, b_update]() {
		b_update();
        if (engine::room == borders::ROOMS::SETTINGS) {
            text = "Ambience volume: ";
            text += "\nSFX volume: ";
            text += "\nResolution: " + std::to_string(engine::resolution_x) + " x " + std::to_string(engine::resolution_y);
            text += "\nFullscreen: "; 
			text += (selected_fullscreen ? "True" : "False");

			sentences[0] = "Ambience volume: ";
			sentences[1] = "SFX volume: ";
			sentences[2] = "Resolution: " + std::to_string(engine::resolution_x) + " x " + std::to_string(engine::resolution_y);
			sentences[3] = "Fullscreen: ";
			sentences[3] += (selected_fullscreen ? "True" : "False");
        }

        if (play_button && play_button->clicked) {
            std::cout << "GOING TO GAME" << std::endl;
            engine::room = borders::ROOMS::CHARACTER_CREATOR;
            engine::change_room = true;

			MainMenu::closeButton(play_button);
			MainMenu::closeButton(settings_button);
			MainMenu::closeButton(exit_button);

        }
        if (settings_button && settings_button->clicked) {
            std::cout << "OPENING SETTINGS" << std::endl;

			row_selection = 0;
            engine::room = borders::ROOMS::SETTINGS;
            engine::change_room = true;

			selected_ambience_volume = engine::ambience_volume;
			selected_sfx_volume = engine::sfx_volume;
			selected_resolution_x = engine::resolution_x;
			selected_resolution_y = engine::resolution_y;
			selected_fullscreen = engine::fullscreen;

            MainMenu::closeButton(play_button);
			MainMenu::closeButton(settings_button);
			MainMenu::closeButton(exit_button);

            back_button = Button::makeButton(1400, 700, 160, 40, std::string("BACK"), Button::TYPES::BACK);
            apply_settings_button = Button::makeButton(1100, 700, 280, 40, std::string("APPLY SETTINGS"), Button::TYPES::APPLY_SETTINGS);
            
		
        }
		if (apply_settings_button && apply_settings_button->clicked) {
			engine::ambience_volume = selected_ambience_volume;
			engine::sfx_volume = selected_sfx_volume;
			engine::resolution_x = selected_resolution_x;
			engine::resolution_y = selected_resolution_y;
			engine::fullscreen = selected_fullscreen;
			
			engine::settings_updated = true;
		}
        if (back_button && back_button->clicked) {
            engine::room = borders::ROOMS::MAIN_MENU;
            engine::change_room = true;

			MainMenu::closeButton(back_button);
			MainMenu::closeButton(apply_settings_button);

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

			Vector2 text_measurement = MeasureTextEx(engine::body_font, sentences[row_selection].c_str(), engine::m_font, engine::spacing);
			Vector2 v1 = Vector2(50 + text_measurement.x + 100, 80 + ((text_measurement.y + engine::spacing) * row_selection));
			Vector2 v2 = Vector2(50 + text_measurement.x + 100, 50 + ((text_measurement.y + engine::spacing) * row_selection));
			Vector2 v3 = Vector2(50 + text_measurement.x + 70, 65 + ((text_measurement.y + engine::spacing) * row_selection));

			std::cout << (text_measurement.y) << std::endl;

			DrawTriangle(v1, v2, v3, BLACK);
			DrawTriangleLines(v1, v2, v3, WHITE);
        }
    };
}

void MainMenu::makeMainMenu() {
    engine::GameObject::objects.push_back(std::move(std::make_unique<MainMenu>()));
}

#endif