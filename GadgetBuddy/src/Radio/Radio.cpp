/**
 * By: Frank Vanris
 * Date: 8/12/2025
 * Desc: Creating a Radio functionality which is the last screen state for this embedded device
*/

#include "Radio.h"
#include <Arduino.h>
#include <Wire.h>
#include "data&states/PinDeclarationsConstants.h"

const char* RADIO_READ_ERROR_MSG = "Radio Read Error!";

// Test settings - DELETE AFTER TESTING
#define FIX_BAND RADIO_BAND_FM
#define FIX_STATION 9810 // 98.10 MHz

Radio::Radio() : mHasError(false) //, mMuteButton(RADIO_MUTE_PIN, RADIO_DEBOUNCE_DELAY)
{}

void Radio::setup() {


    mRadio.init();
    mRadio.setBandFrequency(FIX_BAND, FIX_STATION);
    mRadio.setVolume(2);
    mRadio.setMono(true);

    mHasError = false;
}

void Radio::loop() {

}

const char* Radio::getStationName() const {
    return "Classical 98.1";
}

const char* Radio::getErrorMessage() {
    if(!hasError()) {
        return nullptr;
    }
    return RADIO_READ_ERROR_MSG;
}