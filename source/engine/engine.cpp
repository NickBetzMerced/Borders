#ifndef ENGINE_CPP
#define ENGINE_CPP

#include "engine.h"
#include <map>
#include <iostream>

unsigned int engine::ambience_volume = 100;
unsigned int engine::sfx_volume = 100;
unsigned int engine::resolution_x = 1600;
unsigned int engine::resolution_y = 900;
bool engine::fullscreen = false;
bool engine::settings_updated = false;

unsigned int engine::room = 0;
bool engine::change_room = false;

std::vector<std::unique_ptr<engine::GameObject>> engine::GameObject::objects;
engine::GameObject* engine::GameObject::current_object = nullptr;
bool engine::checked = false;

Camera2D engine::camera = engine::windows::startTemplate(1600, 900, "Borders");

char engine::caret = ' ';
char engine::c = ' ';

Vector2 engine::mouse_pos = GetMousePosition();
Vector2 engine::relative_mouse_pos = {0, 0};
bool engine::l_mouse_clicked = false;

float engine::frame_time = GetFrameTime();

Font engine::title_font = LoadFontEx("./assets/fonts/Audiowide.ttf", engine::l_font, 0, 0);
Font engine::body_font = LoadFontEx("./assets/fonts/Anta.ttf", engine::m_font, 0, 0);    

engine::GameObject::GameObject() {
    parent = nullptr;
    should_close = false;
    x = 0;
    y = 0;
    width = 0;
    height = 0;
    rotation = 0;
    identity = "unassigned";
    visible = false;
    hasMouseEntered = false;
    backspaceTimer = 0;
    mouseHover = [this]() {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            engine::GameObject::current_object = this;
        }
    };
    update = [this]() {
        if (IsKeyDown(KEY_LEFT_SHIFT) && IsKeyPressed(KEY_ENTER) && onShiftEnter) {
            onShiftEnter();
        }
        else if (IsKeyPressed(KEY_ENTER) && onEnter) {
            onEnter();
        }
        if (IsKeyPressed(KEY_ESCAPE) && onEscape) {
            onEscape();
        }
        if (IsKeyPressed(KEY_UP) && onUp) {
            onUp();
        }
        if (IsKeyDown(KEY_UP) && holdUp) {
            holdUp();
        }
        if (IsKeyPressed(KEY_DOWN) && onDown) {
            onDown();
        }
        if (IsKeyDown(KEY_DOWN) && holdDown) {
            holdDown();
        }
        if (IsKeyPressed(KEY_LEFT) && onLeft) {
            onLeft();
        }
        if (IsKeyDown(KEY_LEFT) && holdLeft) {
            holdLeft();
        }
        if (IsKeyPressed(KEY_RIGHT) && onRight) {
            onRight();
        }
        if (IsKeyDown(KEY_RIGHT) && holdRight) {
            holdRight();
        }
        if (IsKeyPressed(KEY_BACKSPACE) && onBackspace) {
            onBackspace();
        }
        if (IsKeyDown(KEY_BACKSPACE) && holdBackspace) {
            holdBackspace();
            backspaceTimer += GetFrameTime();
        }
        if (IsKeyReleased(KEY_BACKSPACE)) {
            backspaceTimer = 0;
        }
        if (IsKeyPressed(KEY_TAB) && onTab) {
            onTab();
        }
        if (!hasMouseEntered && CheckCollisionPointRec(relative_mouse_pos, Rectangle(x, y, width, height))) {
            // mouseEnter();
            hasMouseEntered = true;
            skipCheck = false;
            std::cout << "Mouse entered object " << this << std::endl;
        }
        else if (hasMouseEntered && CheckCollisionPointRec(relative_mouse_pos, Rectangle(x, y, width, height))) {
            mouseHover();
        }
        else if (!skipCheck){
            hasMouseEntered = false;
            skipCheck = true;
            std::cout << "Mouse left object " << this << std::endl;
        }
    };

}


void engine::GameObject::drawAllIndependent() {
    for (auto& object : objects) {
        if (object->drawIndependent) {
            object->drawIndependent();
        }
    }
}
void engine::GameObject::drawAll() {
    for (auto& object : objects) {
        if (object->draw && object->visible) {
            object->draw();
        }
    }
}
void engine::GameObject::drawAllGUI() {
    for (auto& object : objects) {
        if (object->drawGUI) {
            object->drawGUI();
        }
    }
}


void engine::GameObject::updateAll() {
    mouse_pos = GetMousePosition();
    l_mouse_clicked = IsMouseButtonPressed(MOUSE_BUTTON_LEFT);

    frame_time = GetFrameTime();
    float t = GetTime();
    c = GetCharPressed();

	if (settings_updated) {
		if (IsWindowFullscreen() && !engine::fullscreen) {
			ToggleFullscreen();
		}
		else if (!IsWindowFullscreen() && engine::fullscreen) {
			ToggleFullscreen();
		}

		settings_updated = false;
	}
    
    if (fmod(t, engine::caret_delay) < engine::caret_delay / 2) {
            engine::caret = '|';
    }
    else {
        engine::caret = ' ';
    }

    for (unsigned int i = 0; i < objects.size(); i++) {
        engine::GameObject* object = objects[i].get();
        if (object->update && object->should_close == false) {
            object->update();
        }
        if (!checked) {
            if (object->identity == "unassigned") {
                std::cout << "WARNING: OBJECT " << i << " HAS NO IDENTITY ASSIGNED" << std::endl;
            }
        }
    }

    checked = true;

    for (auto it = objects.begin(); it != objects.end(); ) {
        engine::GameObject* object = it->get();
        if (object->should_close == true) {
            it = objects.erase(it);
        } else {
            ++it;
        }
    }
    if (IsKeyPressed(KEY_ESCAPE) && GameObject::objects.size() == 0) {
        engine::exit = true;
    }
}


bool engine::files::exists(const char* file_name) {
    std::ifstream file;
    file.open(file_name);
    return file.is_open();
}
template <typename T>
void engine::files::saveThing(T& thing, std::string file_name, bool append) {
    char* raw_data = (char*)&thing;
    std::ofstream file;

    if (append == false) {
        file.open(file_name, std::ios::trunc);
    }
    else {
        file.open(file_name, std::ios::app);
    }
    
    for (unsigned int i = 0; i < sizeof(T); i++) {
        file << raw_data[i];
    }
    file.close();
}
template <typename T>
void engine::files::loadThing(T* thing, std::string file_name, int& current_byte) {
    std::ifstream file;
    file.open(file_name);

    char ignore;
    for (int i = 0; i < current_byte; i++) {
        file >> ignore;
    }

    for (int i = 0; i < sizeof(T); i++) {
        file >> *((char*)thing + i);
        current_byte += 1;
    }

    file.close();
}

bool engine::cameras::can_move = true;
const float engine::cameras::zoomIncrement = 0.125f;
void engine::cameras::logic(Camera2D& camera) { 
    engine::relative_mouse_pos = GetScreenToWorld2D(GetMousePosition(), camera);

    if (engine::cameras::can_move && IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        Vector2 delta = GetMouseDelta();
        delta = Vector2Scale(delta, -1.0f/camera.zoom);

        camera.target = Vector2Add(camera.target, delta);
    }
    float wheel = GetMouseWheelMove();
    if (wheel != 0) {
        Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        // camera.offset = GetMousePosition();
        camera.target = mouseWorldPos;
        camera.zoom += (wheel * zoomIncrement);
        if (camera.zoom < zoomIncrement) { camera.zoom = zoomIncrement; }
    }
}

void engine::strings::formatFloat(std::string &str, unsigned int precision) {
    int pos = str.find('.');
    while (str.length() - pos > precision + 1) {
        str.pop_back();
    }
}
std::string engine::strings::wrapToBox(std::string input_string, unsigned int window_width, int font_size) {
    unsigned int width = MeasureText(input_string.c_str(), font_size);
    std::string output_string = "";
    unsigned int current_line_length = 0;
    
    std::string word = "";
    for (unsigned int i = 0; i < input_string.length(); i++) {
        if (input_string[i] == ' ') {
            if (current_line_length + word.length() > width) {
                output_string += '\n';
                current_line_length = 0;
            }
            output_string += word + ' ';
            current_line_length += word.length() + 1;
            word = "";
        }
        else {
            word += input_string[i];
        }
    }
    if (current_line_length + word.length() > width) {
        output_string += '\n';
        current_line_length = 0;
    }
    output_string += word;
    current_line_length += word.length();

    return output_string;
}

Camera2D engine::windows::startTemplate(int width, int height, std::string title) {
    SetConfigFlags(FLAG_VSYNC_HINT);
    InitWindow(width, height, title.c_str());
    Camera2D camera = {0};
    camera.target = {0, 0};
    camera.offset = {0, 0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    return camera;
}

std::vector<int> engine::event_tracker::events;
bool engine::event_tracker::exists = false;
engine::event_tracker::event_tracker() {
    exists = true;
    identity = "event tracker";
    update = [this]() {
    };
}
void engine::event_tracker::makeEventTracker() {
    if (exists) {
        std::cout << "Error: event_tracker already exists" << std::endl;
    }
    else {
        engine::GameObject::objects.push_back(std::move(std::make_unique<engine::event_tracker>()));
    }
}

bool engine::global_clock::exists = false;
engine::global_clock::global_clock() {
    count = 0;
    update = [this]() {
        count += GetFrameTime();
        
    };
}


#endif