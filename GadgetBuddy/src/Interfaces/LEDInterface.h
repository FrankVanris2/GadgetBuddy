/**
 * By: Frank Vanris
 * Date: 8/31/2025
 * Desc: Creating an LED Interface
*/

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H
#include "MachineComponentsInterface.h"

class LEDInterface : public MachineComponentsInterface {
public:
    void setup() override = 0;
    void loop() override = 0;

    virtual void turnRed() = 0;
    virtual void turnGreen() = 0;
    virtual void turnYellow() = 0;
    virtual void turnBlue() = 0;
    virtual void turnOff() = 0;
};
#endif