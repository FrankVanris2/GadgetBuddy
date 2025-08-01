/**
 * By: Frank Vanris 
 * Date: 7/30/2025
 * Desc: Creating a RTCClock implementation for the main screen of the GadgetBuddy.
*/

#ifndef RTCCLOCK_H
#define RTCCLOCK_H
#include <RTClib.h>
#include <Arduino.h>
#include "Interfaces/RTCInterface.h"

class RTCClock : public RTCInterface {
public:
    
    // Constructor
    RTCClock();

    void setup() override;

    void loop() override;

    String getDate() {
        return mDateData;
    }

    String getTime() {
        return mTimeData;
    }

    /// @brief Obtaining Error if error occurs within DHT Sensor
    /// @return an error message for what broke
    const char* getErrorMessage() override;

private:
    RTC_DS1307 rtc;
    bool mHasError;

    String mTimeData;
    String mDateData;

    void recordDateAndTime();
    bool isConnectedToComputer();
};
#endif