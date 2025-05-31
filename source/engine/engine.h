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

namespace engine {
    static float backspace_delete_delay = 0.05;

    Vector2 relative_mouse_pos = {0, 0};
    Font font = GetFontDefault();
    int spacing = 4;
    int s_font = 15;
    int m_font = 20;
    int l_font = 30;
    bool exit = false;
    unsigned int room = 0;
    bool change_room = true;

    char c;

    char caret = ' ';
    float caret_delay = 0.5;

    template <typename T>
    struct ArrayList {
        int count;
        int capacity;
        T* data;
        ArrayList();
        ~ArrayList();
        void inflate();
        void append(T item);
        T pop();
        T& operator[](int index);
    };
    struct GameObject {
        bool should_close;
        enum types {unassigned = 0, window = 1, button = 2};
        static std::vector<std::unique_ptr<GameObject>> objects;
        static GameObject* current_object;

        std::function<void()> draw;
        static void drawAll();
        std::function<void()> update;
        static void updateAll();

        int x;
        int y;
        int width;
        int height;
        std::string identity;
        bool visible;
        GameObject();

        std::function<void()> onEnter;
        std::function<void()> onShiftEnter;
        std::function<void()> onTab;
        std::function<void()> onBackspace;
        std::function<void()> holdBackspace;
        float backspaceTimer;
        std::function<void()> onEscape;
        std::function<void()> onUp;
        std::function<void()> onDown;
        std::function<void()> onLeft;
        std::function<void()> onRight;

        std::function<void()> mouseEnter;
        bool hasMouseEntered;
        bool skipCheck;
        std::function<void()> mouseHover;
        std::function<void()> mouseExit;
    };
    struct files {
        bool exists(const char* file_name);
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
    struct strings {
        void formatFloat(std::string &str, unsigned int precision);
        static std::string wrapToBox(std::string input_string, unsigned int window_width, int font_size);
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
    struct global_clock : GameObject {
        double count;
        static bool exists;
        global_clock();
        static void makeGlobalClock();
    };
    
}


#endif