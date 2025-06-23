#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../engine/button.h"
#include "borders.h"

struct MainMenu : engine::GameObject {
	enum {AMBIENCE_INDEX = 0, SFX_INDEX = 1, RESOLUTION_INDEX = 2, FULLSCREEN_INDEX = 3, SETTINS_INDEX_LIMIT = 3, NUMBER_OF_SETTINGS = 4};
    Button* play_button;
    Button* settings_button;
    Button* exit_button;

    Button* back_button;
    Button* apply_settings_button;
    Button* toggle_button;
	Button* resolution_button;

    std::string text;
	std::array<std::string, 4> sentences;

	int selected_ambience_volume;
	int selected_sfx_volume;
	unsigned int selected_resolution_x;
	unsigned int selected_resolution_y;
	bool selected_fullscreen;

	unsigned int row_selection;

    MainMenu();
    static void makeMainMenu();
    
	void closeButton(Button*& button);
};

#endif