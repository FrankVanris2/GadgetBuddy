/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Implementing the LCD Screen for visualization purposes so that the user can see what is occurring visually on the LCDScreen
 */

#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H

#include <LiquidCrystal_I2C.h>
#include "Interfaces/LCDInterface.h"
#include "Interfaces/DisplayStrategy.h"
#include "Interfaces/ErrorReportingInterface.h"
#include "Buttons/Buttons.h"
#include "TempHumidSensor/TempHumidSensor.h"
#include "RTCClock/RTCClock.h"
#include "AirQuality/AirQuality.h"

class LCDScreen : public LCDInterface {
public:

    LCDScreen(Buttons& buttons_ref, TempHumidSensor& temphumid_ref, RTCClock& rtcc_ref, AirQuality& airqual_ref);

    void setup() override;
    void loop() override;

private:

    // Private LCD Implementation details (Not needed within my LCD Interface)
    void updateAndDisplayScreen();
    void displayErrorScreen(const char* errorMessage);
    const char* checkForErrors();

    // Strategy pattern - each screen has its own display strategy
    void initializeDisplayStrategies();
    DisplayStrategy* getCurrentDisplayStrategy();

    LiquidCrystal_I2C lcd;
    int mCurrentScreenState;

    Buttons& mButtonsRef; // Store a reference to the Buttons object
    TempHumidSensor& mTempHumidRef; // Stores a reference to the DHT11 sensor
    RTCClock& mRTCRef; // Stores a reference to the RTCClock
    AirQuality& mAirQualRef;

    // Display strategies for each screen
    DisplayStrategy* mDisplayStrategies[4];

    // Update control
    unsigned long mLastUpdate;
    static const unsigned long UPDATE_INTERVAL = 500;
    bool mForceUpdate;
};

#endif
