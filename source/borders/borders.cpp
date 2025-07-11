#ifndef BORDERS_CPP
#define BORDERS_CPP

#include "borders.h"
#include "player.h"
#include "main_menu.h"

borders::BackgroundStars::BackgroundStars() : engine::GameObject() {
    identity = "Background Stars";
    visible = true;
    texture = LoadTexture("./assets/sprites/background/nebuladrystars.png");
    texture2 = LoadTexture("./assets/sprites/background/nebulawetstars.png");

    update = [this]() {
        wet_layer_offset = Vector2(0, 0) - Vector2Scale(engine::camera.target, 0.1);
        dry_layer_offset = Vector2(0, 0) - Vector2Scale(engine::camera.target, 0.1);
    };

    drawIndependent = [this]() {
        for (int i = -3; i <= 3; i++) {
            for (int j = -3; j <= 3; j++) {
                DrawTextureEx(texture, dry_layer_offset, 0, 1, WHITE);
                DrawTextureEx(texture2, wet_layer_offset, 0, 1, WHITE);
            }
        }
    };
}

void borders::BackgroundStars::makeBackgroundStars() {
    engine::GameObject::objects.push_back(std::move(std::make_unique<BackgroundStars>()));
}

std::function<void()> borders::in_game = []() {
	borders::TimeCycleTracker::makeTimeCycleTracker();
	Player::makePlayer();
	borders::BackgroundStars::makeBackgroundStars();
};

std::function<void()> borders::main_menu = []() {
	engine::GameObject::objects.clear();
	MainMenu::makeMainMenu();
};

borders::TimeCycleTracker* borders::TimeCycleTracker::time_cycle_tracker_ptr = nullptr;

borders::TimeCycleTracker::TimeCycleTracker() : engine::GameObject() {
	day = 0;
	seconds = 0;
	update = [this]() {
		seconds += engine::frame_time;
		if (seconds > static_cast<int>(SECONDS_PER_DAY)) {
			seconds -= static_cast<int>(SECONDS_PER_DAY);
			day += 1;
		}
	};
}

void borders::TimeCycleTracker::makeTimeCycleTracker() {
	std::unique_ptr<borders::TimeCycleTracker> tct_unique_ptr = std::make_unique<borders::TimeCycleTracker>();
	borders::TimeCycleTracker::time_cycle_tracker_ptr = tct_unique_ptr.get();
	engine::GameObject::objects.push_back(std::move(tct_unique_ptr));
}



#endif