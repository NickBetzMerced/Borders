#ifndef CHARACTER_CREATOR_CPP
#define CHARACTER_CREATOR_CPP

#include "character_creator.h"
#include "borders.h"

bool CharacterCreator::exists = false;
CharacterCreator::CharacterCreator() : window(window::TYPES::CHARACTER_CREATOR) {
    row_selection = 0;
    time_since_enter_pressed = 0;


    std::function<void()> b_update;
    b_update = update;

    for (int i = 0; i < NUMBER_OF_LINES; i++) {
        inputs[i] = "";
    }
    for (int i = 0; i < NUMBER_OF_LINES; i++) {
        column_selection[i] = 0;
    }

    update = [b_update, this]() {
        b_update();
        text[0] = "Character name: ";
        text[1] = "Ship name: ";
        text[2] = "Player government name: ";
        text[3] = "Initial Allegiance: ";
        text[4] = "Character Backstory: ";
        text[5] = "Double click enter to finish";

        allegiances[0] = "Human";
        allegiances[1] = "Humanoids";
        allegiances[2] = "Cyborgs";
        allegiances[3] = "Machines";

        backstories[0] = "Trader";
        backstories[1] = "Miner";
        backstories[2] = "Scrapper";
        backstories[3] = "Destroyer";

        for (int i = 0; i < NUMBER_OF_LINES; i++) {
            text[i] += inputs[i];
            if (i == INITIAL_ALLGIANCE_ROW) {
                text[i] += allegiances[column_selection[INITIAL_ALLGIANCE_ROW]];
            }
            else if (i == BACKSTORIES_ROW) {
                text[i] += backstories[column_selection[BACKSTORIES_ROW]];
            }
        }
        
        text[row_selection] += engine::caret;

        if (engine::c != 0 && row_selection < INITIAL_ALLGIANCE_ROW && inputs[row_selection].length() < MAX_INPUT_LENGTH) {
            inputs[row_selection] += engine::c;
        }

        time_since_enter_pressed += GetFrameTime();
    };

    draw = [this]() {
        DrawRectangle(x, y, width, height, WHITE);
        DrawRectangleLinesEx(Rectangle(x, y, width, y + 75), 2, BLACK);
        DrawRectangleLinesEx(Rectangle(x, y, width, height), 2, BLACK);
        DrawTextEx(engine::title_font, title.c_str(), Vector2(x + 5, y + 5), engine::l_font, engine::spacing, BLACK);
        for (unsigned int i = 0; i < CharacterCreator::NUMBER_OF_LINES; i++) {
            DrawTextEx(engine::body_font, text[i].c_str(), Vector2(x + 10, y + 85 + (i * 30)), engine::m_font, engine::spacing, BLACK);
        }
    };

    onUp = [this]() {
        if (row_selection > 0) {
            row_selection--;
        }
    };

    onDown = [this]() {
        if (row_selection < LAST_SELECTABLE_LINE) {
            row_selection++;
        }
    };

    onLeft = [this]() {
        if (column_selection[row_selection] > 0) {
            column_selection[row_selection]--;
        }
    };

    onRight = [this]() {
        if (row_selection == INITIAL_ALLGIANCE_ROW && column_selection[row_selection] < NUMBER_OF_ALLEGIANCES-1) {
            column_selection[row_selection]++;
        }
        else if (row_selection == BACKSTORIES_ROW && column_selection[row_selection] < NUMBER_OF_BACKSTORIES-1) {
            column_selection[row_selection]++;
        }
    };

    onBackspace = [this]() {
        if (!inputs[row_selection].empty()) {
            inputs[row_selection].pop_back();
        }
    };

    holdBackspace = [this]() {
        if (!inputs[row_selection].empty() && backspaceTimer > 0.6) {
            inputs[row_selection].pop_back();
            backspaceTimer -= engine::backspace_delete_delay;
        }
    };

    onEnter = [this]() {
        if (time_since_enter_pressed < 0.5) {
            std::cout << "SAVE CHARACTER" << std::endl;
            std::ofstream character_save;
            character_save.open("./save/player.txt", std::ios::trunc);
            for (int i = 0; i <= LAST_EDITABLE_INDEX; i++) {
                character_save << inputs[i] << "\n";
            }
            for (int i = INITIAL_ALLGIANCE_ROW; i <= BACKSTORIES_ROW; i++) {
                character_save << column_selection[i] << "\n";
            }
            character_save.close();


            should_close = true;
            engine::change_room = true;
            engine::room = space_game::ROOMS::SPACE_GAME;
        }
        time_since_enter_pressed = 0;
    };
}


void CharacterCreator::makeCharacterCreator() {
    engine::GameObject::objects.push_back(std::move(std::make_unique<CharacterCreator>()));
}


#endif