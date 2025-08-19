/**
 * By: Frank Vanris
 * Date: 8/12/2025
 * Desc: Creating a Radio functionality which is the last screen state for this embedded device
*/

#include "Radio.h"
#include <Arduino.h>
#include <Wire.h>

const char* RADIO_READ_ERROR_MSG = "Radio Read Error!";

// Test settings - DELETE AFTER TESTING
#define FIX_BAND RADIO_BAND_FM
#define FIX_STATION 9810 // 98.10 MHz

Radio::Radio() : mHasError(false), mLastUpdate(0) {}

void Radio::setup() {
    Serial.println(F("Initializing Radio setup."));

    Wire.begin();

    // Initialize the Radio
    mRadio.init();

    // Enable debug information
    mRadio.debugEnable();

    // Set to a local FM Station
    mRadio.setBandFrequency(FIX_BAND, FIX_STATION);
    mRadio.setVolume(2);
    mRadio.setMono(true);

    Serial.println(F("Radio setup completed successfully."));
    Serial.print(F("Tuned to: "));
    Serial.print(FIX_STATION / 100.0, 1);
    Serial.println(F(" MHz"));
    mHasError = false;
   
}

void Radio::loop() {
    // Handle radio functionality
    runTEA5767Test(); // - TEMPORARY DELETE AFTER TEST
}

// DELETE AFTER TEST
void Radio::runTEA5767Test() {
    if (mHasError) return;

    unsigned long currentMillis = millis();
    if (currentMillis - mLastUpdate >= TEST_INTERVAL) {
        mLastUpdate = currentMillis;

        char s[12];
        mRadio.formatFrequency(s, sizeof(s));
        Serial.print(F("Station: "));
        Serial.println(s);

        Serial.print(F("Radio: "));
        mRadio.debugRadioInfo();

        Serial.print(F("Audio: "));
        mRadio.debugAudioInfo();

        Serial.println(F("---"));
    }
}

const char* Radio::getErrorMessage() {
    if(!hasError()) {
        return nullptr;
    }
    return RADIO_READ_ERROR_MSG;
}