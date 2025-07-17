/**
 * By: Frank Vanris
 * Date: 7/17/2025
 * Desc: Creating a buttons class to change between different states of the screen.
 */

 #pragma once

 #include "Interfaces/MachineComponentsInterface.h"

 class Buttons : public MachineComponentsInterface {
public:
    Buttons(int leftPin, int rightPin, int minVal, int maxVal, unsigned long debounceDelayMs);

    void setup() override;
    void loop() override;

    void leftButtonDebounce(int reading, unsigned long currentTime);
    void rightButtonDebounce(int reading, unsigned long currentTime);
    

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

    const int LEFT_BUTTON_PIN;
    const int RIGHT_BUTTON_PIN;
    const int MIN_BUTTON_VAL_LIMIT;
    const int MAX_BUTTON_VAL_LIMIT;
    const unsigned long DEBOUNCE_DELAY_MS;
 };

