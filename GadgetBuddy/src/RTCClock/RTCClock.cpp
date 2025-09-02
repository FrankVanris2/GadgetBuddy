/**
 * @file RTCClock.cpp
 * @author Frank Vanris
 * @date 7/30/2025
 * @brief Implementation of the RTCClock class for GadgetBuddy main screen time and date display.
 *
 * This file contains logic for interfacing with the RTC_DS1307 real-time clock,
 * including initialization, time/date formatting, error handling, and integration
 * with the main screen display.
 */

#include "RTCClock.h"

const char* RTC_READ_ERROR_MSG = "RTC Read Error!";

RTCClock::RTCClock() : mHasError(false), mTimeData(""), mDateData("") {}

void RTCClock::setup() {
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

    if (!now.isValid()) {
        mHasError = true;
        mDateData = "";
        mTimeData = "";
        return; 
    }

    mDateData = "";
    mTimeData = "";

    if (now.month() < 10) mDateData += "0";
    mDateData += String(now.month()) + "/";
    if (now.day() < 10) mDateData += "0";
    mDateData += String(now.day()) + "/";
    mDateData += String(now.year());

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
        return false;
   }

   if (millis() < 5000) {
        return true;
   }

   return false;
}