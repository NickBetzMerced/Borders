#include "raylib.h"
#include "./source/borders/character_creator.h"
#include "./source/borders/player.h"
#include "./source/borders/borders.h"
#include "./source/borders/main_menu.h"
#include <unistd.h>
#include <iostream>

using namespace std;


int main () {
    
	engine::rooms.insert({borders::ROOMS::IN_GAME, borders::in_game});
	engine::rooms.insert({borders::ROOMS::MAIN_MENU, borders::main_menu});

	engine::loadAllSettings();

    engine::event_tracker::makeEventTracker();
    
	engine::changeRoom(borders::ROOMS::MAIN_MENU);

    Player* player = nullptr;

    SetExitKey(KEY_NULL);

    while (!engine::exit && !WindowShouldClose()) {
        engine::cameras::logic(engine::camera);
        if (player != nullptr) {
            engine::camera.target = Vector2({player->x - engine::resolution_x / 2, player->y - engine::resolution_y / 2});
        }

        if (engine::room == borders::ROOMS::CHARACTER_CREATOR && engine::changed_room) {
            if (!std::filesystem::exists("./save/player.txt")) {
                engine::changed_room = false;
                CharacterCreator::makeCharacterCreator();
            }
            else {
                engine::changeRoom(borders::ROOMS::IN_GAME);

                for (unsigned int i = 0; i < engine::GameObject::objects.size(); i++) {
                    std::cout << "Object " << i << " : " << (engine::GameObject::objects[i]->identity) 	<< " X: " << engine::GameObject::objects[i]->x << " Y: " << engine::GameObject::objects[i]->y << "\n";
                    if (engine::GameObject::objects[i]->identity == "Player") {
                        player = static_cast<Player*>(engine::GameObject::objects[i].get());
                    }
                }
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
            
			DrawTextEx(engine::body_font, text.c_str(), Vector2(10, engine::resolution_y - 200), engine::m_font, engine::spacing, WHITE);
            engine::GameObject::drawAllGUI();
            
        EndDrawing();
    }
   
    CloseWindow();
    return 0;
}
