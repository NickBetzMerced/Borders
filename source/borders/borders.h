#ifndef BORDERS_H
#define BORDERS_H

#include "../engine/engine.h"

namespace borders {
    enum ROOMS {MAIN_MENU, SETTINGS, CHARACTER_CREATOR, IN_GAME};

    struct BackgroundStars : engine::GameObject {
        Texture2D texture2;
        Vector2 wet_layer_offset;
        Vector2 dry_layer_offset;
        BackgroundStars();
        static void makeBackgroundStars();
    };
}

#endif