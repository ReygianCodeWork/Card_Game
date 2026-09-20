#pragma once
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "QuizManager.hxx"
#include "pinout.hxx"
#include "Display.hxx"

class LCDisplay {
    private:
        DisplayVar disp;
        GameManager &game;
        LiquidCrystal_I2C &lcd;
        uint8_t interval;
        int lastTime;

    public:
        LCDisplay(GameManager&game_, DisplayVar &disp_p, LiquidCrystal_I2C &lcd_d);

        void displayInit();
        void displaying();
};
