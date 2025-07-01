#ifndef ENGINE_H
#define ENGINE_H

#include <fstream>
#include <string>
#include "raylib.h"
#include <functional>
#include <vector>
#include <memory>
#include "raymath.h"
#include <filesystem>
#include <format>
#include <cmath>

namespace engine {
    constexpr double pi = 3.14159265358979323846;

	enum {NUMBER_OF_RESOLUTIONS = 7};
    constexpr std::array<Vector2, NUMBER_OF_RESOLUTIONS> resolutions = {
        Vector2(800, 600),
        Vector2(1280, 720),
        Vector2(1600, 900),
        Vector2(1920, 1080),
		Vector2(2560, 1440),
		Vector2(2560, 1600),
		Vector2(3840, 2160)
    };

    extern unsigned int ambience_volume;
    extern unsigned int sfx_volume;
    extern unsigned int resolution_x;
    extern unsigned int resolution_y;
	extern unsigned int resolution_middle_x;
	extern unsigned int resolution_middle_y;
    extern bool fullscreen;

	extern bool settings_updated;
	extern bool save_settings;

    extern bool checked;
    
    extern float frame_time;
	extern float time;

    constexpr float backspace_delete_delay = 0.05;

    extern Camera2D camera;

    extern bool l_mouse_clicked;
    extern Vector2 mouse_pos;
    extern Vector2 relative_mouse_pos;

    constexpr int spacing = 2;
    constexpr int s_font = 15;
    constexpr int m_font = 30;
    constexpr int l_font = 64;
    extern Font title_font;
    extern Font body_font;

    inline bool exit = false;
    extern unsigned int room;
    extern bool changed_room;

    extern char c;
	extern int key_pressed;

    extern char caret;
    constexpr float caret_delay = 0.5;

	void loadAllSettings();

	void changeRoom(int room);
	extern std::unordered_map<int, std::function<void()>> rooms;

    struct GameObject {
        bool should_close;
        enum types {unassigned = 0, window = 1, button = 2};
        static std::vector<std::unique_ptr<GameObject>> objects;
        static GameObject* current_object;

        std::function<void()> drawIndependent;
        static void drawAllIndependent();
        std::function<void()> draw;
        static void drawAll();
        std::function<void()> drawGUI;
        static void drawAllGUI();
        std::function<void()> update;
        static void updateAll();

        float x;
        float y;
        int width;
        int height;
        float rotation;
        std::string identity;
        bool visible;
        Texture2D texture;

        GameObject* parent;
        std::vector<GameObject*> children;
        GameObject();

        std::function<void()> onEnter;
        std::function<void()> onShiftEnter;
        std::function<void()> onTab;
        std::function<void()> onBackspace;
        std::function<void()> holdBackspace;
        float backspaceTimer;
        std::function<void()> onEscape;
        std::function<void()> onUp;
        std::function<void()> holdUp;
        std::function<void()> onDown;
        std::function<void()> holdDown;
        std::function<void()> onLeft;
        std::function<void()> holdLeft;
        std::function<void()> onRight;
        std::function<void()> holdRight;

        std::function<void()> mouseEnter;
        bool hasMouseEntered;
        bool skipCheck;
        std::function<void()> mouseHover;
        std::function<void()> mouseExit;
    };
    struct files {
        template <typename T>
        static void saveThing(T& thing, std::string file_name, bool append = false);
        template <typename T>
        static void loadThing(T* thing, std::string file_name, int& current_byte);
    };
    struct cameras {
        static bool can_move;
        static void logic(Camera2D& camera);
        static const float zoomIncrement;
    };
    struct windows {
        static Camera2D startTemplate(int width, int height, std::string title);
    };
    struct event_tracker : GameObject {
        enum types {save = 1, load = 2};
        static std::vector<int> events;
        static bool exists;
        event_tracker();
        static void makeEventTracker();
    };
    
}


#endif