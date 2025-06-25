#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.h"

Player::Player() : engine::GameObject() {
    identity = "Player";
    turnRate = 80.0;
    speed = 0;
    acceleration = 20.0;

	fuel = 1000;
	fuel_consumption = 0.02;

    x = engine::resolution_x / 2;
    y = engine::resolution_y / 2;
    visible = true;
    texture = LoadTexture("./assets/sprites/ships/medium/body_02.png");
    float x_half = texture.width / 2;
    float y_half = texture.height / 2;

    hud_text = "";

	inventory_window = nullptr;

    std::function<void()> b_update;
    b_update = update;

    update = [this, b_update]() {
        b_update();
        float rotation_radian = rotation * ((engine::pi) / 180);
        x += cos(rotation_radian) * speed * engine::frame_time;
        y += sin(rotation_radian) * speed * engine::frame_time;
        if (rotation > 360) {
            rotation -= 360;
        }
        else if (rotation < -360) {
            rotation += 360;
        }
        hud_text = std::format("ROTATION: {:.0f} \nSPEED: {:.0f} \nFUEL: {:.1f} GALLONS", rotation, speed, fuel);

		if (engine::key_pressed == KEY_I) {
			if (inventory_window == nullptr) {
				inventory_window = Window::makeWindow(Window::TYPES::INVENTORY);
			}
			else {
				inventory_window->should_close = true;
				inventory_window = nullptr;
			}
		}
    };

    draw = [this, x_half, y_half]() {
        DrawTexturePro(texture, Rectangle{0, 0, (float)texture.width, (float)texture.height}, Rectangle{std::round(x), std::round(y), (float)texture.width, (float)texture.height}, Vector2(x_half, y_half), std::round(rotation), WHITE);
    };
    
    drawGUI = [this]() {
        DrawTextEx(engine::body_font, hud_text.c_str(), Vector2(20, 20), engine::m_font, engine::spacing, WHITE);
    };

    holdLeft = [this]() {
        rotation -= turnRate * engine::frame_time;
    };

    holdRight = [this]() {
        rotation += turnRate * engine::frame_time;
    };

    holdUp = [this]() {
		if (fuel > 0) {
        	speed += acceleration * engine::frame_time;
			fuel -= acceleration * fuel_consumption * engine::frame_time;
		}
    };

    holdDown = [this]() {
        if (speed > 0 && fuel > 0) {
            speed -= acceleration * engine::frame_time;
			fuel -= acceleration * fuel_consumption * engine::frame_time;
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