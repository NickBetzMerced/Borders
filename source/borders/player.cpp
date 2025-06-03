#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.h"

Player::Player() : engine::GameObject() {
    turnRate = 80.0;
    x = 800;
    y = 450;
    visible = true;
    texture = LoadTexture("./assets/sprites/ships/medium/body_02.png");
    float x_half = texture.width / 2;
    float y_half = texture.height / 2;
    draw = [this, x_half, y_half]() {
        DrawTexturePro(texture, Rectangle{0, 0, (float)texture.width, (float)texture.height}, Rectangle{x, y, (float)texture.width, (float)texture.height}, Vector2(x_half, y_half), rotation, WHITE);
    };

    holdLeft = [this]() {
        rotation -= turnRate * GetFrameTime();
        std::cout << "LEFT " << std::endl;
    };

    holdRight = [this]() {
        rotation += turnRate * GetFrameTime();
        std::cout << "RIGHT " << std::endl;
    };
}

void Player::makePlayer() {
    engine::GameObject::objects.push_back(std::move(std::make_unique<Player>()));
}

#endif