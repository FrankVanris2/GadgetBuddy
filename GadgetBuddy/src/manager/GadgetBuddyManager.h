/*
* By: Frank Vanris
* Date: 8/12/2024
* Desc: Contains all the important methods needed for the gadget to work
*/

#ifndef GADGET_BUDDY_MANAGER_H
#define GADGET_BUDDY_MANAGER_H

#include "Interfaces/MachineComponentsInterface.h"
#include "Buttons/Buttons.h"
#include "LCDDisplay/LCDScreen.h"
#include "TempHumidSensor/TempHumidSensor.h"
#include "RTCClock/RTCClock.h"
#include "AirQuality/AirQuality.h"

class GadgetBuddyManager : public MachineComponentsInterface {
public:

    GadgetBuddyManager();

    void setup() override;
    void loop() override;

private:
    Buttons mButtons; // Buttons object as a member
    TempHumidSensor mTempHumidSensor; // DHT11 object as a member
    RTCClock mRtcClock;
    AirQuality mAirQual;
    LCDScreen mLcdScreen; // LCDScreen object as a member
};

extern GadgetBuddyManager gadgetBuddyManager;

#endif