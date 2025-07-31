/**
 * By: Frank Vanris
 * Date: 7/30/2025
 * Desc: Implementing an RTCClock for the main screen.
*/

#include "RTCClock.h"


const char* RTC_READ_ERROR_MSG = "RTC Read Error!";
const char* RTC_NO_ERROR_MSG = nullptr; 

RTCClock::RTCClock() : mHasError(false) {}

void RTCClock::setup() {

}

void RTCClock::loop() {

}

void RTCClock::recordDateAndTime() {

}

const char* RTCClock::getErrorMessage() {
    if(mHasError) {
        return RTC_READ_ERROR_MSG;
    }
    return RTC_NO_ERROR_MSG;
}