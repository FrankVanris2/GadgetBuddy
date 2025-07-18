/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Implementing the LCD Screen for visualization purposes so that the user can see what is occurring visually on the LCDScreen
 */

#pragma once

#include <LiquidCrystal_I2C.h>
#include "Interfaces/MachineComponentsInterface.h"
#include "Buttons/Buttons.h"

class LCDScreen : public MachineComponentsInterface {
public:

    LCDScreen(Buttons& buttons_ref);

    void setup() override;
    void loop() override;

private:

    // for testing purposes
    void updateAndDisplayScreen();

    // Displayed information
    void displayMainScreen();
    void displayTemp_HumidityScreen();
    void displayAirQualityScreen();
    void displayRadioScreen();

    LiquidCrystal_I2C lcd;
    int mCurrentScreenState;
    Buttons& mButtonsRef; // Store a reference to the Buttons object
};
