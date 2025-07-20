/**
 * By: Frank Vanris
 * Date: 7/20/2025
 * Desc: Creating an LCD Display Interface which will allow me to unit test certain components later
 * in the future.
 */

 #pragma once

 #include "MachineComponentsInterface.h"

class LCDInterface : public MachineComponentsInterface {
public:
    virtual ~LCDInterface() = default;

    void setup() override = 0;
    void loop() override = 0;

private:

    // Updates the LCD Display.
    virtual void updateAndDisplayScreen() = 0;

    // Display main screen Screen
    virtual void displayMainScreen() = 0;

    // Display Temperature/Humidity Screen
    virtual void displayTemp_HumidityScreen() = 0;

    // Display Air Quality Screen.
    virtual void displayAirQualityScreen() = 0;

    // Display Radio Screen.
    virtual void displayRadioScreen() = 0;

    // Display Error Message if needed
    virtual void displayErrorScreen(const char* errorMessage) = 0;
};