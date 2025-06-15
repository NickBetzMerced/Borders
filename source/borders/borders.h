#ifndef BORDERS_H
#define BORDERS_H

#include "../engine/engine.cpp"

namespace borders {
    enum ROOMS {MAIN_MENU = 1, SPACE_GAME = 2};

    struct BackgroundStars : engine::GameObject {
        Texture2D texture2;
        Vector2 wet_layer_offset;
        Vector2 dry_layer_offset;
        BackgroundStars();
        static void makeBackgroundStars();
    };
}

#endif