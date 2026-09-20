#include "Input.hxx"
#include "pinout.hxx"
#include <Arduino.h>
#include <vector>


Input::Input(GameManager &game_) : game(game_) {}

void Input::inputInit() {
    for (size_t i = 0; i < inputPins.size(); i++) {
        pinMode(inputPins[i], INPUT_PULLUP);
    }
    lastButtonState = HIGH;
}

void Input::readInput_Buttons() {
    /*
    int buttonA = digitalRead(BUTTON_A);
    int buttonB = digitalRead(BUTTON_B);
    int buttonC = digitalRead(BUTTON_C);
    int buttonD = digitalRead(BUTTON_D);
    */

    for (size_t i = 0; i < inputPins.size(); i++) {
        inputButtons.push_back(digitalRead(inputPins[i]));
    }

    if (int button = onePress(inputButtons); button) 
    {
        game.setButton(button);
        game.buttonPress();

        if(button != lastButtonState) {
            lastDebounceTime = millis();
            lastButtonState = button;
        }
        
        if ((millis() - lastDebounceTime) >= DEBOUNCE_DELAY) {
            static int stableButtonState = HIGH; 

    // If the steady state has actually changed
            if (button != stableButtonState) {
                 stableButtonState = button;

      // Because of INPUT_PULLUP, LOW means the button is pressed down
                if (stableButtonState == LOW) {
                    Serial.println("Button Pressed cleanly (No Double Triggering!)");
                }
            }
        }
    }

    inputButtons.clear();
}

bool Input::onePress(std::vector<int> buttons) {

}



