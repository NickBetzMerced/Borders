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

    Texture2D background = LoadTexture("./assets/sprites/background/stars.jpg");
    
    if (!std::filesystem::exists("./save/player.txt")) {
        CharacterCreator::makeCharacterCreator();
    }
    else {
        Player::makePlayer();
    }

    if (!std::filesystem::exists("./assets/sprites/background/stars.jpg")) {
        std::cout << "STARS DOES NOT EXIST" << std::endl;
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
        engine::cameras::logic(camera);
        camera.target = Vector2({player->x - 800, player->y - 450});
        camera.offset = Vector2({800 - (800) * camera.zoom, 450 - (450) * camera.zoom});
        if (IsKeyPressed(KEY_F3)) {
            std::cout << "CAMERA ZOOM: " << camera.zoom << std::endl;
            std::cout << "CAMERA TARGET: " << camera.target.x << " x " << camera.target.y << std::endl;
            std::cout << "CAMERA OFFSET: " << camera.offset.x << " x " << camera.offset.y << std::endl;
        }
        engine::GameObject::updateAll();

        Vector2 mouse = GetMousePosition();
        std::string text = std::format("MOUSE X: {:.0f} MOUSE Y: {:.0f} \nRELATIVE MOUSE X: {:.0f} RELATIVE MOUSE Y: {:.0f} \nCAMERA TARGET: {:.0f} x {:.0f}\nCAMERA OFFSET:  {:.0f} x {:.0f}", mouse.x, mouse.y, engine::relative_mouse_pos.x, engine::relative_mouse_pos.y, camera.target.x, camera.target.y, camera.offset.x, camera.offset.y);
        BeginDrawing();
            BeginMode2D(camera);
            DrawTextureEx(background, Vector2(0, 0), 0, 0.25, WHITE);
            engine::GameObject::drawAll();

            
            ClearBackground(BLACK);
            EndMode2D();
            engine::GameObject::drawAllIndependent();
            DrawTextEx(engine::body_font, text.c_str(), Vector2(10, 700), engine::m_font, engine::spacing, WHITE);
        EndDrawing();
    }
   
    CloseWindow();
    return 0;
}
