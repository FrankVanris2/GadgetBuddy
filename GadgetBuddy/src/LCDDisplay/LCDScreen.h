/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Implementing the LCD Screen for visualization purposes so that the user can see what is occurring visually on the LCDScreen
 */

#pragma once

#include <LiquidCrystal_I2C.h>
#include "Interfaces/LCDInterface.h"
#include "Buttons/Buttons.h"

class LCDScreen : public LCDInterface {
public:

    LCDScreen(Buttons& buttons_ref);

    void setup() override;
    void loop() override;

private:

    // for testing purposes
    void updateAndDisplayScreen() override;

    // Displayed information
    void displayMainScreen() override;
    void displayTemp_HumidityScreen() override;
    void displayAirQualityScreen() override;
    void displayRadioScreen() override;

    LiquidCrystal_I2C lcd;
    int mCurrentScreenState;
    Buttons& mButtonsRef; // Store a reference to the Buttons object
};
