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
    RadioButtons(int leftPin, int rightPin);

    void setup() override;
    void loop() override;

private:
    int mLeftButton;
    int mRightButton;
};

#endif
