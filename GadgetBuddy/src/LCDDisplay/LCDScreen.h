/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Implementing the LCD Screen for visualization purposes so that the user can see what is occurring visually on the LCDScreen
 */

#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H

#include <LiquidCrystal_I2C.h>
#include "Interfaces/LCDInterface.h"
#include "Buttons/Buttons.h"
#include "TempHumidSensor/TempHumidSensor.h"
#include "RTCClock/RTCClock.h"

class LCDScreen : public LCDInterface {
public:

    LCDScreen(Buttons& buttons_ref, TempHumidSensor& temphumid_ref, RTCClock& rtcc_ref);

    void setup() override;
    void loop() override;

private:

    // Private LCD Implementation details (Not needed within my LCD Interface)
    void updateAndDisplayScreen();
    void displayMainScreen();
    void displayTemp_HumidityScreen();
    void displayAirQualityScreen();
    void displayRadioScreen();
    void displayErrorScreen(const char* errorMessage);

    LiquidCrystal_I2C lcd;
    int mCurrentScreenState;
    Buttons& mButtonsRef; // Store a reference to the Buttons object
    TempHumidSensor& mTempHumidRef; // Stores a reference to the DHT11 sensor
    RTCClock& mRTCRef; // Stores a reference to the RTCClock
};

#endif
