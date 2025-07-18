/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Implementing the LCD Screen for visualization purposes so that the user can see what is occurring visually on the LCDScreen
 */

#pragma once
 #include  "data&states/ScreenStates.h"

#include <LiquidCrystal_I2C.h>
#include "Interfaces/MachineComponentsInterface.h"
#include "Buttons/Buttons.h"

class LCDScreen : MachineComponentsInterface {
public:

    LCDScreen(Buttons& buttons_ref);

    void setup() override;
    void loop() override;

    // for testing purposes
    void screenStateChanges(int screenState);

    // Displayed information
    void displayMainScreen();
    void displayTemp_HumidityScreen();
    void displayAirQualityScreen();
    void displayRadioScreen();

    void setScreenState(int screenState) {
        mScreenChange = screenState;
    }

private:
    LiquidCrystal_I2C lcd;
    int mScreenChange;
    Buttons& mButtonsRef; // Store a reference to the Buttons object
    ScreenStates screenStates;
};
