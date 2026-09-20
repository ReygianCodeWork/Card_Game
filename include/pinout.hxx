#pragma once
#include <vector>

constexpr uint8_t SCL = 22;
constexpr uint8_t SDA = 21;

constexpr uint8_t BUTTON_A = 34;
constexpr uint8_t BUTTON_B = 35;
constexpr uint8_t BUTTON_C = 32;
constexpr uint8_t BUTTON_D = 33;

constexpr uint8_t DEBOUNCE_DELAY = 50;

std::vector<uint8_t> inputPins = {
    BUTTON_A,
    BUTTON_B,
    BUTTON_C,
    BUTTON_D
};