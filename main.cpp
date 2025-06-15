#include "raylib.h"
#include "./source/borders/character_creator.cpp"
#include "./source/borders/player.cpp"
#include "./source/borders/borders.cpp"
#include "./source/borders/main_menu.cpp"
#include <unistd.h>


using namespace std;


int main () {
    engine::title_font = LoadFontEx("./assets/fonts/Audiowide.ttf", engine::l_font, 0, 0);
    engine::body_font = LoadFontEx("./assets/fonts/Anta.ttf", engine::m_font, 0, 0);    

    borders::BackgroundStars::makeBackgroundStars();
    engine::event_tracker::makeEventTracker();
    
    MainMenu::makeMainMenu();

    if (!std::filesystem::exists("./save/player.txt")) {
        CharacterCreator::makeCharacterCreator();
    }
    else {
        Player::makePlayer();
    }

    Player* player;

    for (unsigned int i = 0; i < engine::GameObject::objects.size(); i++) {
        std::cout << "Object " << i << "\n";
        if (engine::GameObject::objects[i]->identity == "Player") {
            player = static_cast<Player*>(engine::GameObject::objects[i].get());
        }
    }

    SetExitKey(KEY_NULL);
    while (!engine::exit && !WindowShouldClose()) {
        engine::cameras::logic(engine::camera);
        engine::camera.target = Vector2({player->x - 800, player->y - 450});
        engine::camera.offset = Vector2({800 - (800) * engine::camera.zoom, 450 - (450) * engine::camera.zoom});
        
        

        engine::GameObject::updateAll();

        Vector2 mouse = GetMousePosition();
        std::string text = std::format("MOUSE X: {:.0f} MOUSE Y: {:.0f} \nRELATIVE MOUSE X: {:.0f} RELATIVE MOUSE Y: {:.0f} \nCAMERA TARGET: {:.0f} x {:.0f}\nCAMERA OFFSET:  {:.0f} x {:.0f}", mouse.x, mouse.y, engine::relative_mouse_pos.x, engine::relative_mouse_pos.y, engine::camera.target.x, engine::camera.target.y, engine::camera.offset.x, engine::camera.offset.y);
        BeginDrawing();
            ClearBackground(BLACK);
            
            engine::GameObject::drawAllIndependent();

            BeginMode2D(engine::camera);
            
            engine::GameObject::drawAll();

            EndMode2D();
            
            engine::GameObject::drawAllGUI();
            DrawTextEx(engine::body_font, text.c_str(), Vector2(10, 700), engine::m_font, engine::spacing, WHITE);
        EndDrawing();
    }
   
    CloseWindow();
    return 0;
}
