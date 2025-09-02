/**
 * @file GadgetBuddyManager.h
 * @author Frank Vanris
 * @date 8/12/2024
 * @brief Central manager for GadgetBuddy, coordinating all hardware modules and main logic.
 *
 * This class contains all essential methods and member objects required for the device to operate.
 * It initializes, manages, and coordinates the LED, buttons, LCD screen, temperature/humidity sensor,
 * RTC clock, air quality sensor, and compass modules.
 */

#ifndef GADGET_BUDDY_MANAGER_H
#define GADGET_BUDDY_MANAGER_H

#include "Interfaces/MachineComponentsInterface.h"
#include "LED/LED.h"
#include "Buttons/Buttons.h"
#include "LCDDisplay/LCDScreen.h"
#include "TempHumidSensor/TempHumidSensor.h"
#include "RTCClock/RTCClock.h"
#include "AirQuality/AirQuality.h"
#include "Compass/Compass.h"

/**
 * @class GadgetBuddyManager
 * @brief Central manager class for GadgetBuddy device.
 */
class GadgetBuddyManager : public MachineComponentsInterface {
public:
    /**
     * @brief Constructor.
     */
    GadgetBuddyManager();

    /**
     * @brief Initialize all hardware modules and device state.
     */
    void setup() override;

    /**
     * @brief Main loop for updating device logic and hardware modules.
     */
    void loop() override;

private:
    LED mLed;                       ///< LED module
    Buttons mButtons;               ///< Buttons module
    TempHumidSensor mTempHumidSensor; ///< Temperature/Humidity sensor module
    RTCClock mRtcClock;             ///< RTC clock module
    AirQuality mAirQual;            ///< Air quality sensor module
    Compass mCompass;               ///< Compass module
    LCDScreen mLcdScreen;           ///< LCD screen module
};

/**
 * @brief Global instance of GadgetBuddyManager for main application use.
 */
extern GadgetBuddyManager gadgetBuddyManager;

#endif