/**
 * By: Frank Vanris
 * Date: 8/19/2025
 * Desc: Creating Radio Buttons that are meant to switch between different stations of the radio
*/

#include "RadioButtons.h"
#include <Arduino.h>

RadioButtons::RadioButtons(int muteButton, unsigned long debounceDelay)
    : mMuteButton(muteButton), 
    mIsMuted(false), 
    mLastRawState(HIGH),
    mDebouncedState(HIGH),
    mLastDebounceTimer(0),
    mDebounceDelay(debounceDelay)
{}

void RadioButtons::setup() {
    pinMode(mMuteButton, INPUT_PULLUP);

    // Initialize button state
    mDebouncedState = digitalRead(mMuteButton);
    mLastRawState = mDebouncedState;

}

void RadioButtons::loop() {
    updateButtonState();
}


void RadioButtons::processButtonDebounce(int currentReading, unsigned long currentTime,
                               int& lastRawState, int& debouncedState,
                               unsigned long& lastDebounceTimer,
                               bool isLeftButton) {
    // Check if the button state has changed
    if (currentReading != lastRawState) {
        lastDebounceTimer = currentTime; // Reset the debounce timer
    }

    // If the button state has been stable for the debounce delay, update the debounced state
    if ((currentTime - lastDebounceTimer) > mDebounceDelay) {
        if (currentReading != debouncedState) {
            debouncedState = currentReading;
        }
    }

    lastRawState = currentReading; // Update the last raw state
}
void RadioButtons::updateButtonState() {
    bool reading = digitalRead(mMuteButton);
    unsigned long currentTime = millis();

    // Use the interface method with our member variables
    processButtonDebounce(reading, currentTime,
                           mLastRawState, mDebouncedState,
                           mLastDebounceTimer, false);
}

bool RadioButtons::wasMutePressed() {
    bool lastButtonState = HIGH;
    bool currentButtonState = mDebouncedState;
    bool pressed = (lastButtonState == HIGH && currentButtonState == LOW);
    lastButtonState = currentButtonState;
    return pressed;
}


