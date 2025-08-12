/**
 * By: Frank Vanris
 * Date: 8/12/2025
 * Desc: Creating a Radio functionality which is the last screen state for this embedded device
*/

#include "Radio.h"
#include <Arduino.h>

const char* RADIO_READ_ERROR_MSG = "Radio Read Error!";

Radio::Radio() : mHasError(false) {}

void Radio::setup() {
    // Initialize radio settings
}

void Radio::loop() {
    // Handle radio functionality
}

const char* Radio::getErrorMessage() {
    if(!hasError()) {
        return nullptr;
    }
    return RADIO_READ_ERROR_MSG;
}