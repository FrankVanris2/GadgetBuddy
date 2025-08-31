/**
 * By: Frank Vanris 
 * Date: 8/31/2025
 * Desc: Creating an LED class that is meant to light up the LED when there are warnings to keep track of.
*/

#ifndef LED_H
#define LED_H
#include "Interfaces/LEDInterface.h"
#include "data&states/ScreenStates.h"

class LED : public LEDInterface {
public:
    LED(int redPin, int greenPin, int bluePin);

    void setup() override;

    void loop() override;

    // color changes
    void turnRed() override;
    void turnGreen() override;
    void turnYellow() override;
    void turnBlue() override;
    void turnOff() override;

    // helper method 
    void updateLEDForScreen(ScreenStates state, float temp, float airQuality, LED& led);

private:
    int mRedPin;
    int mGreenPin;
    int mBluePin;
};
#endif