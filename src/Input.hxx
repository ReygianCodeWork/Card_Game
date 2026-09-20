#pragma once
#include "GameManager.hxx"
#include <vector>

class Input {
    private:
        GameManager &game;
        int lastDebounceTime;
        int lastButtonState;
        int stableButtonState;
        std::vector<int> inputButtons;

        bool onePress(std::vector<int> buttons);

    public:
        Input(GameManager &game_);
        void inputInit();
        void readInput_Buttons();
};
