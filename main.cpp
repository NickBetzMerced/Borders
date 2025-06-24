#include "raylib.h"
#include "./source/borders/character_creator.h"
#include "./source/borders/player.h"
#include "./source/borders/borders.h"
#include "./source/borders/main_menu.h"
#include <unistd.h>
#include <iostream>

using namespace std;


int main () {
    
    engine::event_tracker::makeEventTracker();
    
    MainMenu::makeMainMenu();

    Player* player = nullptr;

    SetExitKey(KEY_NULL);
    while (!engine::exit && !WindowShouldClose()) {
        engine::cameras::logic(engine::camera);
        if (player != nullptr) {
            engine::camera.target = Vector2({player->x - engine::resolution_x / 2, player->y - engine::resolution_y / 2});
        }

        if (engine::room == borders::ROOMS::CHARACTER_CREATOR && engine::change_room) {
            if (!std::filesystem::exists("./save/player.txt")) {
                engine::change_room = false;
                CharacterCreator::makeCharacterCreator();
            }
            else {
                Player::makePlayer();
                borders::BackgroundStars::makeBackgroundStars();

                for (unsigned int i = 0; i < engine::GameObject::objects.size(); i++) {
                    std::cout << "Object " << i << "\n";
                    if (engine::GameObject::objects[i]->identity == "Player") {
                        player = static_cast<Player*>(engine::GameObject::objects[i].get());
                    }
                }

                engine::room = borders::ROOMS::IN_GAME;
                engine::change_room = true;
            }
        }

        engine::camera.offset = Vector2({engine::resolution_x / 2 - (engine::resolution_x / 2) * engine::camera.zoom, engine::resolution_y / 2 - (engine::resolution_y / 2) * engine::camera.zoom});
        
        

        engine::GameObject::updateAll();

        std::string text = std::format("MOUSE X: {:.0f} MOUSE Y: {:.0f} \nRELATIVE MOUSE X: {:.0f} RELATIVE MOUSE Y: {:.0f} \nCAMERA TARGET: {:.0f} x {:.0f}\nCAMERA OFFSET:  {:.0f} x {:.0f}", engine::mouse_pos.x, engine::mouse_pos.y, engine::relative_mouse_pos.x, engine::relative_mouse_pos.y, engine::camera.target.x, engine::camera.target.y, engine::camera.offset.x, engine::camera.offset.y);
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
