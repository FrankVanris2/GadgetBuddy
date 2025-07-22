/**
 * By: Frank Vanris
 * Date: 7/17/2025
 * Desc: I will be defining a buttons class that will change between the states of the screen. 
 * (Current goal: click a button see the counter increase on the Display screen)
 */

 #include <Arduino.h>
#include "Buttons.h"

// Constructor
Buttons::Buttons(int leftPin, int rightPin, int minVal, int maxVal, unsigned long debounceDelayMs) :
    mButtonVal(minVal),
    mL_LastButtonState(LOW),
    mR_LastButtonState(LOW),
    mLButtonState(LOW), 
    mRButtonState(LOW), 
    lLastDebounceTime(0), 
    rLastDebounceTime(0), 
    LEFT_BUTTON_PIN(leftPin),
    RIGHT_BUTTON_PIN(rightPin),
    MIN_BUTTON_VAL_LIMIT(minVal),
    MAX_BUTTON_VAL_LIMIT(maxVal),
    DEBOUNCE_DELAY_MS(debounceDelayMs)
{}

// setup function for my buttons
void Buttons::setup() {
    pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
}

// loop function for my buttons
void Buttons::loop() {
    // Read the current state of the buttons
    int lReading = digitalRead(LEFT_BUTTON_PIN);
    int rReading = digitalRead(RIGHT_BUTTON_PIN);
    unsigned long currentTime = millis();

    // --- LEFT BUTTON DEBOUNCE AND LOGIC ---
    processButtonDebounce(lReading, currentTime, 
                          mL_LastButtonState, mLButtonState, 
                          lLastDebounceTime, true);

    // --- RIGHT BUTTON DEBOUNCE AND LOGIC ---
    processButtonDebounce(rReading, currentTime, 
                          mR_LastButtonState, mRButtonState, 
                          rLastDebounceTime, false);
}

// Generalizes the debounce and action logic for a single button
void Buttons::processButtonDebounce(int currentReading, unsigned long currentTime,
                                    int& lastRawState, int& debouncedState,
                                    unsigned long& lastDebounceTimer, 
                                    bool isLeftButton) {

    if (currentReading != lastRawState) {
        lastDebounceTimer = currentTime;
    }

    if ((currentTime - lastDebounceTimer) > DEBOUNCE_DELAY_MS) {
        if (currentReading != debouncedState) {
            debouncedState = currentReading;

            if (debouncedState == LOW) {
                if (isLeftButton) {
                    if (mButtonVal > MIN_BUTTON_VAL_LIMIT) {
                        mButtonVal--;
                    }
                } else {
                    if(mButtonVal < MAX_BUTTON_VAL_LIMIT) {
                        mButtonVal++;
                    }
                }
            }
        }
    }
    lastRawState = currentReading;
}