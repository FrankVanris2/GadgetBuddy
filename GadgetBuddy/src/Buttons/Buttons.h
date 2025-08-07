/**
 * By: Frank Vanris
 * Date: 7/17/2025
 * Desc: Creating a buttons class to change between different states of the screen.
 */

 #ifndef BUTTONS_H
 #define BUTTONS_H

 #include "Interfaces/ButtonInterface.h"

 class Buttons : public ButtonInterface {
public:
    Buttons(int leftPin, int rightPin, int minVal, int maxVal, unsigned long debounceDelayMs);

    void setup() override;
    void loop() override;

    int getButtonVal() {
        return mButtonVal;
    }

private:
    int mButtonVal;
    int mL_LastButtonState; 
    int mR_LastButtonState; 
    int mLButtonState;      
    int mRButtonState;      
    unsigned long lLastDebounceTime; 
    unsigned long rLastDebounceTime; 

    // Configuration parameters (now const member variables)
    const int LEFT_BUTTON_PIN;
    const int RIGHT_BUTTON_PIN;
    const int MIN_BUTTON_VAL_LIMIT;
    const int MAX_BUTTON_VAL_LIMIT;
    const unsigned long DEBOUNCE_DELAY_MS;

    // Private helper function
    void processButtonDebounce(int currentReading, unsigned long currentTime,
                               int& lastRawState, int& debouncedState,
                               unsigned long& lastDebounceTimer,
                               bool isLeftButton) override;
 };

 #endif

