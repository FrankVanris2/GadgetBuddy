/**
 * By: Frank Vanris
 * Date: 8/12/2025
 * Desc: Creating a Radio functionality which is the last screen state for this embedded device
*/

#include "Radio.h"
#include <Arduino.h>
#include <Wire.h>
#include <radio.h>
#include "data&states/PinDeclarationsConstants.h"

const char* RADIO_READ_ERROR_MSG = "Radio Read Error!";

#define FIX_BAND RADIO_BAND_FM
#define FIX_STATION 9810 // 98.10 MHz

// Create a dedicated I2C bus instance ONLY for the radio
TwoWire radioI2C = TwoWire(1);

Radio::Radio() : mHasError(false) //, mMuteButton(RADIO_MUTE_PIN, RADIO_DEBOUNCE_DELAY)
{}

void Radio::setup() {

    radioI2C.begin(RADIO_SDA_PIN, RADIO_SCL_PIN);
    radioI2C.setClock(100000);

    // 2. Initialize the radio library, PASSING IT our dedicated I2C bus
    if(!mRadio.initWire(radioI2C)) {
        mHasError = true;
        return;
    }

    // 3. Now that it's initialized on the correct bus, configure the radio
    // using the standard library function
    mRadio.setBand(FIX_BAND);
    mRadio.setFrequency(FIX_STATION);
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