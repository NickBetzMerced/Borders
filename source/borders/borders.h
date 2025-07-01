#ifndef BORDERS_H
#define BORDERS_H

#include "../engine/engine.h"

struct MainMenu;

namespace borders {
    enum ROOMS {MAIN_MENU, SETTINGS, CHARACTER_CREATOR, IN_GAME};

	extern std::function<void()> in_game;
	extern std::function<void()> main_menu;

    struct BackgroundStars : engine::GameObject {
        Texture2D texture2;
        Vector2 wet_layer_offset;
        Vector2 dry_layer_offset;
        BackgroundStars();
        static void makeBackgroundStars();
    };
}

#endif