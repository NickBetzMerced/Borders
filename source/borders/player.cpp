#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.h"

Player::Player() : engine::GameObject() {
    turnRate = 80.0;
    speed = 0;
    acceleration = 10.0;
    x = 800;
    y = 450;
    visible = true;
    texture = LoadTexture("./assets/sprites/ships/medium/body_02.png");
    float x_half = texture.width / 2;
    float y_half = texture.height / 2;

    hud_text = "";

    std::function<void()> b_update;
    b_update = update;

    update = [this, b_update]() {
        b_update();
        float rotation_radian = rotation * ((engine::pi) / 180);
        x += cos(rotation_radian) * speed * GetFrameTime();
        y += sin(rotation_radian) * speed * GetFrameTime();
        if (rotation > 360) {
            rotation -= 360;
        }
        else if (rotation < -360) {
            rotation += 360;
        }
        hud_text = std::format("ROTATION: {:.0f} \nSPEED: {:.0f}", rotation, speed);
    };

    draw = [this, x_half, y_half]() {
        DrawTexturePro(texture, Rectangle{0, 0, (float)texture.width, (float)texture.height}, Rectangle{std::round(x), std::round(y), (float)texture.width, (float)texture.height}, Vector2(x_half, y_half), rotation, WHITE);
        DrawTextEx(engine::body_font, hud_text.c_str(), Vector2(20, 20), engine::m_font, engine::spacing, WHITE);
    };

    holdLeft = [this]() {
        rotation -= turnRate * GetFrameTime();
        std::cout << "LEFT " << std::endl;
    };

    holdRight = [this]() {
        rotation += turnRate * GetFrameTime();
        std::cout << "RIGHT " << std::endl;
    };

    holdUp = [this]() {
        speed += acceleration * GetFrameTime();
    };

    holdDown = [this]() {
        if (speed > 0) {
            speed -= acceleration * GetFrameTime();
        }
        else {
            speed = 0;
        }
    };
}

void Player::makePlayer() {
    engine::GameObject::objects.push_back(std::move(std::make_unique<Player>()));
}

#endif