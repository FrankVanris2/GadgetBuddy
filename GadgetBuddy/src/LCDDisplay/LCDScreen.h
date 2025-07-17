/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Implementing the LCD Screen for visualization purposes so that the user can see what is occurring visually on the LCDScreen
 */

#pragma once

#include "Interfaces/MachineComponentsInterface.h"


class LCDScreen : MachineComponentsInterface {
public:

    LCDScreen();

    void setup() override;
    void loop() override;

    // for testing purposes
    void testPrintButtonMechanic();

private:
    int mScreenChange;
};

// Singelton
extern LCDScreen lcdScreen;