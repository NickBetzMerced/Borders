#ifndef PLAYER_CPP
#define PLAYER_CPP

#include "player.h"
#include "borders.h"
#include "item.h"
#include "inventory_window.h"
#include <iostream>

Player* Player::player_ptr = nullptr;

Player::Player() : Ship(Ship::TYPES::SHUTTLE) {
    identity = "Player";
    turn_rate = 80.0;
    speed = 0;
    acceleration = 4.8;

	fuel_consumption = 0.002;

	inventory = {Item(Item::TYPES::URANIUM, (float)1)};
	parts = {ShipPart(ShipPart::SIMPLE_DORM), ShipPart(ShipPart::FISSION_ENGINE), ShipPart(ShipPart::SMALL_CARGO_BAY)};
	mass = frame_mass;
	for (unsigned int i = 0; i < parts.size(); i++) {
		mass += parts[i].mass;
	}
	fuel_ptr = &inventory[0];

    x = engine::resolution_x / 2;
    y = engine::resolution_y / 2;
    visible = true;
    texture = LoadTexture("./assets/sprites/ships/medium/body_02.png");
    float x_half = texture.width / 2;
    float y_half = texture.height / 2;

    hud_text = "";

	inventory_window = nullptr;

	crew.push_back(Person());
	power_draw = crew.size() * 0.000006;

    std::function<void()> b_update;
    b_update = update;

    update = [this, b_update]() {
		power_draw = crew.size() * 0.000006;
		fuel_ptr->consume(power_draw * engine::frame_time);
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
        hud_text = std::format("ROTATION: {:.0f} \nSPEED: {:.0f} \nURANIUM: {:.1f} KG\nDAY: {}", rotation, speed, fuel_ptr->getMass(), borders::TimeCycleTracker::time_cycle_tracker_ptr->day);
		hud_text_2 = "ENERGY: "; 
		float time_left = (fuel_ptr->getMass() / power_draw);
		time_left = std::clamp(time_left, 0.0f, 75000.0f);
		if (time_left > static_cast<float>(borders::TimeCycleTracker::SECONDS_PER_DAY)) {
			float days_left = time_left / static_cast<float>(borders::TimeCycleTracker::SECONDS_PER_DAY);
			if (days_left > 365) {
				float years_left = std::clamp(days_left / 365, 0.0f, 10.0f);
				hud_text_2 += std::format("\nYEARS LEFT: {:.1f}", years_left);
				if (years_left >= 10.0f) {
					hud_text_2 += "+";
				}
			}
			else {
				hud_text_2 += std::format("\nDAYS LEFT: {:.1f}", days_left);
			}
		}
		else {
			hud_text_2 += std::format("\nSECONDS LEFT: {:.1f}", time_left);
		}

		if (engine::key_pressed == KEY_I) {
			if (inventory_window == nullptr) {
				inventory_window = InventoryWindow::makeInventoryWindow();
			}
			else {
				inventory_window->should_close = true;
				inventory_window = nullptr;
			}
		}
		if (engine::key_pressed == KEY_ESCAPE) {
			engine::changeRoom(borders::ROOMS::MAIN_MENU);
		}
    };

    draw = [this, x_half, y_half]() {
        DrawTexturePro(texture, Rectangle{0, 0, (float)texture.width, (float)texture.height}, Rectangle{std::round(x), std::round(y), (float)texture.width, (float)texture.height}, Vector2(x_half, y_half), std::round(rotation), WHITE);
    };
    
    drawGUI = [this]() {
        DrawTextEx(engine::body_font, hud_text.c_str(), Vector2(20, 20), engine::m_font, engine::spacing, WHITE);
		DrawTextEx(engine::body_font, hud_text_2.c_str(), Vector2(engine::resolution_x - MeasureTextEx(engine::body_font, hud_text_2.c_str(), engine::m_font, engine::spacing).x - 20, 20), engine::m_font, engine::spacing, WHITE);
    };

    holdLeft = [this]() {
        rotation -= turn_rate * engine::frame_time;
    };

    holdRight = [this]() {
        rotation += turn_rate * engine::frame_time;
    };

    holdUp = [this]() {
		if (fuel_ptr->getMass() > 0.00005) {
        	speed += acceleration * engine::frame_time;
			fuel_ptr->consume(acceleration * fuel_consumption * engine::frame_time);
			power_draw += acceleration * fuel_consumption;
		}
    };

    holdDown = [this]() {
        if (speed > 0 && fuel_ptr->getMass() > 0.00005) {
            speed -= acceleration * engine::frame_time;
			fuel_ptr->consume(acceleration * fuel_consumption * engine::frame_time);
			power_draw += acceleration * fuel_consumption;
        }
        else if (speed < 0) {
            speed = 0;
        }
    };
}

void Player::makePlayer() {
    std::unique_ptr<Player> player = std::make_unique<Player>();
	Player::player_ptr = player.get();
	engine::GameObject::objects.push_back(std::move(player));
}

#endif