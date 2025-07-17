/**
 * By: Frank Vanris
 * Date: 7/17/2025
 * Desc: Creating a buttons class to change between different states of the screen.
 */

 #pragma once

 #include "Interfaces/MachineComponentsInterface.h"

 class Buttons : public MachineComponentsInterface {
public:
    Buttons();

    void setup() override;
    void loop() override;

    int getButtonVal() {
        return mButtonVal;
    }
private:
    int mButtonVal;
    int mLButtonState;
    int mRButtonState;
    
    bool mLIsPressed;
    bool mRIsPressed;

 };

 extern Buttons buttons;