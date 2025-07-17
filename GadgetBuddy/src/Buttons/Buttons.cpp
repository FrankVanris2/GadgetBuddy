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
    mButtonVal(0),
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
    leftButtonDebounce(lReading, currentTime);
    
    // --- RIGHT BUTTON DEBOUNCE AND LOGIC ---
    rightButtonDebounce(rReading, currentTime);
}

// Left button debounce logic
void Buttons::leftButtonDebounce(int reading, unsigned long currentTime) {
    if (reading != mL_LastButtonState) {
        lLastDebounceTime = currentTime;
    }

    if ((currentTime - lLastDebounceTime) > DEBOUNCE_DELAY_MS) {
        
        if (reading != mLButtonState) {
            mLButtonState = reading; 

            if (mLButtonState == LOW) {
                if (mButtonVal > MIN_BUTTON_VAL_LIMIT) {
                    mButtonVal--;
                }
            }
        }
    }
    mL_LastButtonState = reading; 
}

// Right button debounce logic
void Buttons::rightButtonDebounce(int reading, unsigned long currentTime) {
    if (reading != mR_LastButtonState) {
        rLastDebounceTime = currentTime;
    }

    if ((currentTime - rLastDebounceTime) > DEBOUNCE_DELAY_MS) {
        if (reading != mRButtonState) {
            mRButtonState = reading; 
            if (mRButtonState == LOW) { 
                if (mButtonVal < MAX_BUTTON_VAL_LIMIT) { 
                    mButtonVal++;
                }
            }
        }
    }
    mR_LastButtonState = reading;
}