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

	identity = "Main Menu";

    back_button = nullptr;
    apply_settings_button = nullptr;
    toggle_button = nullptr;
	resolution_button = nullptr;

    play_button = Button::makeButton(engine::resolution_middle_x, engine::resolution_middle_y - 100, 160, 40, std::string("PLAY"));
	settings_button = Button::makeButton(engine::resolution_middle_x, engine::resolution_middle_y, 160, 40, std::string("SETTINGS"));
	exit_button = Button::makeButton(engine::resolution_middle_x, engine::resolution_middle_y + 100, 160, 40, std::string("EXIT"));


	row_selection = 0;
	for (int i = 0; i < NUMBER_OF_SETTINGS; i++) {
		column_selection[i] = 0;
	}

	Vector2 target = Vector2(engine::resolution_x, engine::resolution_y);
	auto it = std::find(engine::resolutions.begin(), engine::resolutions.end(), target);
	if (it != engine::resolutions.end()) {
		column_selection[RESOLUTION_INDEX] = std::distance(engine::resolutions.begin(), it);
	}
	else {
		column_selection[RESOLUTION_INDEX] = 0;
	}
	column_selection[AMBIENCE_INDEX] = engine::ambience_volume;
	column_selection[SFX_INDEX] = engine::sfx_volume;

	column_limits[FULLSCREEN_INDEX] = 0;
	column_limits[AMBIENCE_INDEX] = 100;
	column_limits[SFX_INDEX] = 100;

	target = Vector2(GetMonitorWidth(GetCurrentMonitor()), GetMonitorHeight(GetCurrentMonitor()));
	it = std::find(engine::resolutions.begin(), engine::resolutions.end(), target);

	column_limits[RESOLUTION_INDEX] = std::distance(engine::resolutions.begin(), it);

	selected_ambience_volume = engine::ambience_volume;
	selected_sfx_volume = engine::sfx_volume;

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
		else {
			if (column_selection[row_selection] > 0) {
				column_selection[row_selection] -= 1;
			}
		}
	};
	onRight = [this]() {
		if (row_selection == FULLSCREEN_INDEX) {
			selected_fullscreen = !selected_fullscreen;
		}
		else {
			if (column_selection[row_selection] < column_limits[row_selection]) {
				column_selection[row_selection] += 1;
			}
		}
	};

	std::function<void()> b_update = update;
    update = [this, b_update]() {
		b_update();

		selected_ambience_volume = column_selection[AMBIENCE_INDEX];
		selected_sfx_volume = column_selection[SFX_INDEX];
		selected_resolution_x = engine::resolutions[column_selection[RESOLUTION_INDEX]].x;
		selected_resolution_y = engine::resolutions[column_selection[RESOLUTION_INDEX]].y;

        if (engine::room == borders::ROOMS::SETTINGS) {
            text = "Ambience volume: " + std::to_string(selected_ambience_volume);
            text += "\nSFX volume: " + std::to_string(selected_sfx_volume);
            text += "\nResolution: " + std::to_string(selected_resolution_x) + " x " + std::to_string(selected_resolution_y);
            text += "\nFullscreen: "; 
			text += (selected_fullscreen ? "True" : "False");

			sentences[0] = "Ambience volume: ";
			sentences[1] = "SFX volume: ";
			sentences[2] = "Resolution: " + std::to_string(selected_resolution_x) + " x " + std::to_string(selected_resolution_y);
			sentences[3] = "Fullscreen: ";
			sentences[3] += (selected_fullscreen ? "True" : "False");
        }

        if (play_button && play_button->clicked) {
            std::cout << "GOING TO GAME" << std::endl;
            engine::changeRoom(borders::ROOMS::CHARACTER_CREATOR);

			MainMenu::closeButton(play_button);
			MainMenu::closeButton(settings_button);
			MainMenu::closeButton(exit_button);

			should_close = true;
        }
        else if (settings_button && settings_button->clicked) {
            std::cout << "OPENING SETTINGS" << std::endl;

			row_selection = 0;
            engine::changeRoom(borders::ROOMS::SETTINGS);

			selected_ambience_volume = engine::ambience_volume;
			selected_sfx_volume = engine::sfx_volume;
			selected_resolution_x = engine::resolution_x;
			selected_resolution_y = engine::resolution_y;
			selected_fullscreen = engine::fullscreen;

            MainMenu::closeButton(play_button);
			MainMenu::closeButton(settings_button);
			MainMenu::closeButton(exit_button);

            back_button = Button::makeButton(engine::resolution_x - 200, engine::resolution_y - 100, 160, 40, std::string("BACK"));
            apply_settings_button = Button::makeButton(engine::resolution_x - 500, engine::resolution_y - 100, 280, 40, std::string("APPLY SETTINGS"));
            
		
        }
		else if (apply_settings_button && apply_settings_button->clicked) {
			engine::ambience_volume = selected_ambience_volume;
			engine::sfx_volume = selected_sfx_volume;
			engine::resolution_x = selected_resolution_x;
			engine::resolution_y = selected_resolution_y;
			engine::fullscreen = selected_fullscreen;
			
			engine::settings_updated = true;
			engine::save_settings = true;

			MainMenu::closeButton(back_button);
			MainMenu::closeButton(apply_settings_button);
			back_button = Button::makeButton(engine::resolution_x - 200, engine::resolution_y - 100, 160, 40, std::string("BACK"));
            apply_settings_button = Button::makeButton(engine::resolution_x - 500, engine::resolution_y - 100, 280, 40, std::string("APPLY SETTINGS"));
		}
        else if (back_button && (back_button->clicked || engine::key_pressed == KEY_ESCAPE)) {
			MainMenu::closeButton(back_button);
			MainMenu::closeButton(apply_settings_button);
            engine::changeRoom(borders::ROOMS::MAIN_MENU);
        }
        else if (exit_button && (exit_button->clicked)) {
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

			DrawTriangle(v1, v2, v3, BLACK);
			DrawTriangleLines(v1, v2, v3, WHITE);
        }
    };
}

void MainMenu::makeMainMenu() {
    engine::GameObject::objects.push_back(std::move(std::make_unique<MainMenu>()));
}

#endif