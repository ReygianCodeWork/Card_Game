// src/main.cpp
#include <Arduino.h>
#include <WiFi.h>
#include <LittleFS.h>
#include "QuizManager.hxx"
#include "WebServerManager.hxx"

const char *ssid = "ESP32_Card_Quiz_Game";

QuizManager quiz;
WebServerManager webServer(quiz); // Inject quiz engine into web instance

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
    
    Serial.println("System Ready.");
}

void loop() {
    webServer.handleClient();
    
    // Future sensor polling loop logic goes here!
}
