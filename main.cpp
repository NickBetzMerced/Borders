#include "raylib.h"
#include "./source/borders/character_creator.cpp"
#include "./source/borders/player.cpp"
#include <unistd.h>


using namespace std;


int main () {
    Camera2D camera = engine::windows::startTemplate(1600, 900, "Borders");
    engine::title_font = LoadFontEx("./assets/fonts/Audiowide.ttf", engine::l_font, 0, 0);
    engine::body_font = LoadFontEx("./assets/fonts/Anta.ttf", engine::m_font, 0, 0);    

    engine::event_tracker::makeEventTracker();
    if (!std::filesystem::exists("./save/player.txt")) {
        CharacterCreator::makeCharacterCreator();
    }
    else {
        Player::makePlayer();
        std::cout << "MADE PLAYER" << std::endl;
    }
    for (unsigned int i = 0; i < engine::GameObject::objects.size(); i++) {
        std::cout << "Object " << i << "\n";
    }
    SetExitKey(KEY_NULL);
    while (!engine::exit && !WindowShouldClose()) {
        engine::cameras::logic(camera);
        engine::GameObject::updateAll();
        BeginDrawing();
            BeginMode2D(camera);
            engine::GameObject::drawAll();
            ClearBackground(BLACK);
            EndMode2D();
        EndDrawing();
    }
   
    CloseWindow();
    return 0;
}
