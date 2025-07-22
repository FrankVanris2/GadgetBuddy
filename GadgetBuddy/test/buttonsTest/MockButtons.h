/**
 * By: Frank Vanris
 * Date: 7/22/2025
 * Desc: Mocking the Buttons class for testing purposes
 */

 #pragma once

class MockButtons {
public:
    MockButtons(int leftPin, int rightPin, int minVal, int maxVal, unsigned long debounceDelay) :
        mButtonVal(minVal),
        LEFT_BUTTON_PIN(leftPin),
        RIGHT_BUTTON_PIN(rightPin),
        MIN_BUTTON_VAL_LIMIT(minVal),
        MAX_BUTTON_VAL_LIMIT(maxVal),
        DEBOUNCE_DELAY_MS(debounceDelay),
        _currentTime(0)
    {}

    void setup() {
        // Mock setup
    }

    // Test helper to simulate button press
    void simulateLeftButtonPress() {
        if (mButtonVal > MIN_BUTTON_VAL_LIMIT) {
            mButtonVal--;
        }
    }

    void simulateRightButtonPress() {
        if (mButtonVal < MAX_BUTTON_VAL_LIMIT) {
            mButtonVal++;
        }
    }

    int getButtonVal() {
        return mButtonVal;
    }

    // Test helper to set time
    void setMockTime(unsigned long time) {
        _currentTime = time;
    }

private:
    int mButtonVal;
    const int LEFT_BUTTON_PIN;
    const int RIGHT_BUTTON_PIN;
    const int MIN_BUTTON_VAL_LIMIT;
    const int MAX_BUTTON_VAL_LIMIT;
    const unsigned long DEBOUNCE_DELAY_MS;
    unsigned long _currentTime;
};