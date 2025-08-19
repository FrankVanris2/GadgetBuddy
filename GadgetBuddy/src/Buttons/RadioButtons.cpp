/**
 * By: Frank Vanris
 * Date: 8/19/2025
 * Desc: Creating Radio Buttons that are meant to switch between different stations of the radio
*/

#include "RadioButtons.h"
#include <Arduino.h>

RadioButtons::RadioButtons(int leftButton, int rightButton)
    : mLeftButton(leftButton), mRightButton(rightButton) {}

void RadioButtons::setup() {
    pinMode(mLeftButton, INPUT_PULLUP);
    pinMode(mRightButton, INPUT_PULLUP);
}

void RadioButtons::loop() {
    // Implement the logic for switching radio stations
}
