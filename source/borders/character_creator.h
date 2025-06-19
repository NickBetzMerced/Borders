#ifndef CHARACTER_CREATOR_H
#define CHARACTER_CREATOR_H

#include "../engine/window.h"

struct CharacterCreator : Window {
    enum {INITIAL_ALLGIANCE_ROW = 3, LAST_EDITABLE_INDEX = 3, BACKSTORIES_ROW = 4, LAST_SELECTABLE_LINE = 4, NUMBER_OF_BACKSTORIES = 4, NUMBER_OF_ALLEGIANCES = 4, NUMBER_OF_LINES = 6, MAX_INPUT_LENGTH = 20};
    static bool exists;
    CharacterCreator();
    static void makeCharacterCreator();

    std::array<std::string, NUMBER_OF_LINES> text;
    std::array<std::string, NUMBER_OF_LINES> inputs;
    std::array<std::string, NUMBER_OF_ALLEGIANCES> allegiances;
    std::array<std::string, NUMBER_OF_BACKSTORIES> backstories;

    int row_selection;
    
    std::array<int, NUMBER_OF_LINES> column_selection;

    float time_since_enter_pressed;
};

#endif