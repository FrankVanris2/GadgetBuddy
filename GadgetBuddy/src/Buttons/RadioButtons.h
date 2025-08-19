/**
 * By: Frank Vanris
 * Date: 8/19/2025
 * Desc: Creating Radio Buttons that are meant to switch between different stations of the radio
*/

#ifndef RADIO_BUTTONS_H
#define RADIO_BUTTONS_H

#include "Interfaces/ButtonInterface.h"

class RadioButtons : public ButtonInterface {
public:
    RadioButtons(int muteButton, unsigned long debounceDelay);

    void setup() override;
    void loop() override;

    void processButtonDebounce(int currentReading, unsigned long currentTime,
                               int& lastRawState, int& debouncedState,
                               unsigned long& lastDebounceTimer,
                               bool isLeftButton) override;

    // Mute functionality
    bool wasMutePressed();
    bool isMuted() const { return mIsMuted; }

private:
    int mMuteButton;
    bool mIsMuted;

    // Button state tracking for interface compatibility
    int mLastRawState;
    int mDebouncedState;
    unsigned long mLastDebounceTimer;
    unsigned long mDebounceDelay;

    void updateButtonState();
};

#endif
