/**
 * @file LED.cpp
 * @author Frank Vanris
 * @date 8/31/2025
 * @brief Implementation of the LED class for GadgetBuddy, managing RGB LED states and behaviors.
 *
 * This file contains logic for controlling an RGB LED to indicate device status,
 * including color changes for temperature and air quality warnings, and integration
 * with screen state logic.
 */

#include "LED.h"
#include <Arduino.h>

LED::LED(int redPin, int greenPin, int bluePin) :
    mRedPin(redPin), mGreenPin(greenPin), mBluePin(bluePin) {
}

void LED::setup() {
    pinMode(mRedPin, OUTPUT);
    pinMode(mGreenPin, OUTPUT);
    pinMode(mBluePin, OUTPUT);
}

void LED::loop() {}

void LED::updateLEDForScreen(ScreenStates state, float temp, float airQuality, LED& led) {
    switch (state) {
        case ScreenStates::TEMP_HUMID_SCREEN:
            if (temp < 15.0f || temp > 32.0f) {
                led.turnRed();
            } else if (temp < 18.0f || temp >28.0f) {
                led.turnYellow();
            } else {
                led.turnGreen();
            }
            break;
        case ScreenStates::AIR_QUALITY_SCREEN:
            if (airQuality < 40.0f) {
                led.turnGreen();
            } else if (airQuality < 60.0f) {
                led.turnYellow();
            } else {
                led.turnRed();
            }
            break;
        default:
            led.turnOff();
            break;
    }
}

void LED::turnRed() {
    analogWrite(mRedPin, 255);
    analogWrite(mGreenPin, 0);
    analogWrite(mBluePin, 0);
}

void LED::turnYellow() {
    analogWrite(mRedPin, 255);
    analogWrite(mGreenPin, 255);
    analogWrite(mBluePin, 0);
}

void LED::turnGreen() {
    analogWrite(mRedPin, 0);
    analogWrite(mGreenPin, 255);
    analogWrite(mBluePin, 0);
}

void LED::turnBlue() {
    analogWrite(mRedPin, 0);
    analogWrite(mGreenPin, 0);
    analogWrite(mBluePin, 255);
}

void LED::turnOff() {
    analogWrite(mRedPin, 0);
    analogWrite(mGreenPin, 0);
    analogWrite(mBluePin, 0);
}