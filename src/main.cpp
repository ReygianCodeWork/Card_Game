// src/main.cpp
#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include <LiquidCrystal_I2C.h>
#include "QuizManager.hxx"
#include "WebServerManager.hxx"
#include "Display.hxx"
#include "Input.hxx"
#include "Displayvar.hxx"
#include "GameManager.hxx"

const char *ssid = "ESP32_Card_Quiz_Game";

LiquidCrystal_I2C lcd(0x27, 16, 2);
QuizManager quiz;
GameManager game(quiz);

DisplayVar disp;
WebServerManager webServer(quiz); // Inject quiz engine into web instance
LCDisplay lcd_display(game, disp, lcd);
Input input(game);


void setup() {
    Serial.begin(115200);
    delay(1000);

    if (!LittleFS.begin(true)) {
        Serial.println("An Error has occurred while mounting LittleFS");
        return;
    }

    WiFi.softAP(ssid, "", 1, 0, 1);
    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());

    quiz.loadMockQuestions();
    webServer.begin();
    lcd_display.displayInit();
    input.inputInit();

    Serial.println("System Ready.");
}

void loop() {
    webServer.handleClient();
    // Future sensor polling loop logic goes here!
    input.readInput_Buttons();
    lcd_display.displaying();
}
