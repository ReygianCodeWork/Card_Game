#include "Display.hxx"
#include "Displayvar.hxx"
#include <Arduino.h>
#include <Wire.h>
#include "pinout.hxx"
#include "GameManager.hxx"

LCDisplay::LCDisplay(GameManager& game_, DisplayVar &disp_p, LiquidCrystal_I2C &lcd_d) : game(game_), disp(disp_p), lcd(lcd_d) {}

void LCDisplay::displayInit(){
    disp.timer = 15000;
    disp.score = 0;
    interval = 1000;
    int lastTime = 0;

    Wire.begin(SDA, SCL);
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Quiz Ready!");
}


void LCDisplay::displaying() {

if (!game.gameOver()) {
    int currentTime = millis();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Score: " + String(disp.score));
    lcd.setCursor(0, 1);
    lcd.print("Time: " + String(disp.timer));

    if (currentTime - lastTime >= interval) {
        disp.timer -= interval;
        lastTime = currentTime;
    }

    if (disp.timer == 0) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Next Question");
        disp.timer = 15000;
    }
}
else {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("**Game Over**");

    lcd.setCursor(0, 1);
    lcd.print("Final Score: " + String(disp.score));
}

}



