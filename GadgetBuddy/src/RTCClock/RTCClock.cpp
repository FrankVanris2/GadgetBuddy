/**
 * By: Frank Vanris
 * Date: 7/30/2025
 * Desc: Implementing an RTCClock for the main screen.
*/

#include "RTCClock.h"
#include "data&states/PinDeclarationsConstants.h"


const char* RTC_READ_ERROR_MSG = "RTC Read Error!";

RTCClock::RTCClock() : mHasError(false), mTimeData(""), mDateData("") {}

void RTCClock::setup() {
    // Setting up rtc module:
    if(!rtc.begin()) {
        mHasError = true;
    }


    if (isConnectedToComputer()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    } 
}

void RTCClock::loop() {   
    recordDateAndTime();
}

void RTCClock::recordDateAndTime() {
    if (mHasError) {
        return; 
    }

    DateTime now = rtc.now();

    // Check if RTC is running (valid time)
    if (!now.isValid()) {
        mHasError = true;
        mDateData = "";
        mTimeData = "";
        return; 
    }

    // Clear strings before formatting
    mDateData = "";
    mTimeData = "";

    // Formatted Date as: "MM/DD/YYYY"
    if (now.month() < 10) mDateData += "0";
    mDateData += String(now.month()) + "/";
    if (now.day() < 10) mDateData += "0";
    mDateData += String(now.day()) + "/";
    mDateData += String(now.year());

    // Formatted Time as: "HH:MM:SS" in 24-hour format
    if (now.hour() < 10) mTimeData += "0";
    mTimeData += String(now.hour()) + ":";
    if (now.minute() < 10) mTimeData += "0";
    mTimeData += String(now.minute()) + ":";
    if (now.second() < 10) mTimeData += "0";
    mTimeData += String(now.second());
}

const char* RTCClock::getErrorMessage() {
    if(mHasError) {
        return RTC_READ_ERROR_MSG;
    }
    return nullptr;
}

bool RTCClock::isConnectedToComputer() {
   if (!Serial) {
        return false; // Not connected to a computer
   }

   if (millis() < 5000) {
        return true;
   }

   return false;
}