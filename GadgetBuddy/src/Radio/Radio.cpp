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

Radio::Radio() : mHasError(false), mIsMuted(true), mMuteButton(RADIO_MUTE_PIN, RADIO_DEBOUNCE_DELAY)
{}

void Radio::setup() {
    Serial.println(F("Initializing Radio setup."));

    mMuteButton.setup();
    Wire.begin();

    // Initialize the Radio
    mRadio.init();
    mRadio.setBandFrequency(FIX_BAND, FIX_STATION);
    mRadio.setVolume(0);
    mRadio.setMono(true); // I have a mono setup change if needed

    mHasError = false;   
}

void Radio::loop() {
    mMuteButton.loop();
    handleMuteButton();
}

void Radio::handleMuteButton() {
    if (mMuteButton.wasMutePressed()) {
        Serial.println(F("Mute button pressed, toggling state"));
        toggleMute();

        Serial.print(F("Radio is now: "));
        Serial.println(mIsMuted ? F("MUTED") : F("PLAYING"));
    }
}
void Radio::setMute(bool muted) { 
    mIsMuted = muted;
    if (mIsMuted) {
        mRadio.setVolume(0);
    } else {
        mRadio.setVolume(2);
    }
}

void Radio::toggleMute() {
    setMute(!mIsMuted);
}

const char* Radio::getStationName() const {
    return "Classical 98.1";
}

float Radio::getFrequency() const {
    return CLASSICAL_STATION / 100.0;
}

const char* Radio::getErrorMessage() {
    if(!hasError()) {
        return nullptr;
    }
    return RADIO_READ_ERROR_MSG;
}