/*
* By: Frank Vanris
* Date: 8/12/2024
* Desc: Contains all the important methods needed for the gadget to work
*/

#pragma once
#include "Interfaces/MachineComponentsInterface.h"
#include "Buttons/Buttons.h"
#include "LCDDisplay/LCDScreen.h"
#include "TempHumidSensor/TempHumidSensor.h"

class GadgetBuddyManager : public MachineComponentsInterface {
public:

    GadgetBuddyManager();

    void setup() override;
    void loop() override;

private:
    Buttons mButtons; // Buttons object as a member
    LCDScreen mLcdScreen; // LCDScreen object as a member
    TempHumidSensor mTempHumidSensor; // DHT11 object as a member
};

extern GadgetBuddyManager gadgetBuddyManager;