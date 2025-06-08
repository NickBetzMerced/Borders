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

    Texture2D background = LoadTexture("./assets/sprites/background/nebulawetstars.png");
    
    if (!std::filesystem::exists("./save/player.txt")) {
        CharacterCreator::makeCharacterCreator();
    }
    else {
        Player::makePlayer();
    }

    std::cout << "Stars background texture: " << background.width << " x " << background.height << std::endl;

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
        
        Vector2 layer_1_offset = Vector2Scale(camera.target, 0.1);

        engine::GameObject::updateAll();

        Vector2 mouse = GetMousePosition();
        std::string text = std::format("MOUSE X: {:.0f} MOUSE Y: {:.0f} \nRELATIVE MOUSE X: {:.0f} RELATIVE MOUSE Y: {:.0f} \nCAMERA TARGET: {:.0f} x {:.0f}\nCAMERA OFFSET:  {:.0f} x {:.0f}", mouse.x, mouse.y, engine::relative_mouse_pos.x, engine::relative_mouse_pos.y, camera.target.x, camera.target.y, camera.offset.x, camera.offset.y);
        BeginDrawing();
            ClearBackground(BLACK);
            for (int i = -3; i <= 3; i++) {
                for (int j = -3; j <= 3; j++) {
                    DrawTextureEx(background, Vector2(-layer_1_offset.x + i * background.width * 0.25, -layer_1_offset.y + j * background.height * 0.25), 0, 0.25, WHITE);
                }
            }
            BeginMode2D(camera);
            
            engine::GameObject::drawAll();

            EndMode2D();
            
            engine::GameObject::drawAllIndependent();
            DrawTextEx(engine::body_font, text.c_str(), Vector2(10, 700), engine::m_font, engine::spacing, WHITE);
        EndDrawing();
    }
   
    CloseWindow();
    return 0;
}
