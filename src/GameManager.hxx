#pragma once
#include <Arduino.h>
#include "QuizManager.hxx"


class GameManager {
    private:
        QuizManager &quiz;
        bool isGameOver;
        bool isButtonPress;
        int button;
        int isRestart;

    public:
        GameManager(QuizManager& quiz_);

        // The Game will be over if the question is already exhusted
        bool gameOver();

        void buttonPress();

        void setButton(int button);

        void sendInfo();
};