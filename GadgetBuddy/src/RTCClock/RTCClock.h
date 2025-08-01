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
#include "Interfaces/ErrorReportingInterface.h"

class RTCClock : public RTCInterface, public ErrorReportingInterface {
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

    // ErrorReportingInterface methods
    const char* getErrorMessage() override;
    bool hasError() override { return mHasError; }
    void clearError() override { mHasError = false; }

private:
    RTC_DS1307 rtc;
    bool mHasError;

    String mTimeData;
    String mDateData;

    void recordDateAndTime();
    bool isConnectedToComputer();
};
#endif