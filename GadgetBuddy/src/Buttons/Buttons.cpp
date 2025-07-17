/**
 * By: Frank Vanris
 * Date: 7/17/2025
 * Desc: I will be defining a buttons class that will change between the states of the screen. 
 * (Current goal: click a button see the counter increase on the Display screen)
 */

 #include <Arduino.h>
 #include "Buttons.h"

 #define MAX_BUTTON_VAL 3
 #define MIN_BUTTON_VAL 0

 const int LEFT_BUTTON = 13;
 const int RIGHT_BUTTON = 12;

 // Singelton
 Buttons buttons;
 
 // Constructor (will be updated later)
 Buttons::Buttons() : 
    mButtonVal(0), 
    mLButtonState(LOW), 
    mRButtonState(LOW),
    mLIsPressed(false),
    mRIsPressed(false)
{}

 // setup function for my buttons
 void Buttons::setup() {
    pinMode(LEFT_BUTTON, INPUT);
    pinMode(RIGHT_BUTTON, INPUT);
 }

 // loop function for my buttons
 void Buttons::loop() {

    // Reading states of buttons
    int lButtonState = digitalRead(LEFT_BUTTON);
    int rButtonState = digitalRead(RIGHT_BUTTON);

    //left check
    if(lButtonState != mLButtonState) {
        if(lButtonState == HIGH && mLIsPressed == false) {
            if(mButtonVal > MIN_BUTTON_VAL) {
                mButtonVal--;
            }
            mLIsPressed = true;
        } else if(lButtonState == LOW && mLIsPressed == true) {
            mLIsPressed = false;
        }
        mLButtonState = lButtonState;
    }

    //right check
    if(rButtonState != mRButtonState) {
        if(rButtonState == HIGH && mRIsPressed == false) {
            if(mButtonVal < MAX_BUTTON_VAL) {
                mButtonVal++;
            }
            mRIsPressed = true;
        } else if(rButtonState == LOW && mRIsPressed == true) {
            mRIsPressed = false;
        }
        mRButtonState = rButtonState;
    }

 }

