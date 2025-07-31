/**
 * By: Frank Vanris
 * Date: 7/30/2025
 * Desc: Implementing an RTCClock for the main screen.
*/

#include "RTCClock.h"


const char* RTC_READ_ERROR_MSG = "RTC Read Error!";
const char* RTC_NO_ERROR_MSG = nullptr; 

RTCClock::RTCClock() : mHasError(false), mTimeData(""), mDateData("") {}

void RTCClock::setup() {
    // Setting up rtc module:
    if(!rtc.begin()) {
        mHasError = true;
    }

    // automatically sets date and time on PC
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
}

void RTCClock::loop() {
    
    recordDateAndTime();
}

void RTCClock::recordDateAndTime() {
    if (mHasError) {
        return; // Don't try to read if RTC failed to initialize
    }

    DateTime now = rtc.now();

    // Check if RTC is running (valid time)
    if (!now.isValid()) {
        mHasError = true;
        mDateData = "";
        mTimeData = "";
        return; 
    }

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
    return RTC_NO_ERROR_MSG;
}