/**
 * By: Frank Vanris
 * Date: 8/12/2025
 * Desc: Creating a Radio class that implements the RadioInterface.
*/

#ifndef RADIO_H
#define RADIO_H
#include "Interfaces/RadioInterface.h"
#include "Interfaces/ErrorReportingInterface.h"
#include <radio.h>
#include <Wire.h>
#include <TEA5767.h>
#include "Buttons/RadioButtons.h"

class Radio : public RadioInterface, public ErrorReportingInterface {
public:
    Radio();

    void setup() override;
    void loop() override;

    // Adding mute functionality?
    void setMute(bool muted);
    bool isMuted() const { return mIsMuted; }
    void toggleMute();

    // Station info for LCD Display
    const char* getStationName() const;
    float getFrequency() const;

    // ErrorReportingInterface implementation
    const char* getErrorMessage() override;
    bool hasError() override { return mHasError; }
    void clearError() override { mHasError = false; }

private:
    TEA5767 mRadio;
    bool mHasError;
    bool mIsMuted;

    // ADDING RADIO BUTTONS TO RADIO CLASS
    RadioButtons mMuteButton;

    // Test variables - DELETE AFTER TESTING
    static const int CLASSICAL_STATION = 9810; //98.1 MHz
    static const int RADIO_BAND = RADIO_BAND_FM;

    void handleMuteButton();
};

#endif