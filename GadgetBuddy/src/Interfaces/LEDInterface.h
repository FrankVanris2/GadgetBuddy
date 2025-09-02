/**
 * @file LEDInterface.h
 * @author Frank Vanris
 * @date 8/31/2025
 * @brief Interface for LED control in GadgetBuddy.
 *
 * This abstract class defines the required methods for LED implementations,
 * supporting modularity and enabling flexible color/status indication.
 */

#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include "MachineComponentsInterface.h"

/**
 * @class LEDInterface
 * @brief Abstract interface for LED modules.
 */
class LEDInterface : public MachineComponentsInterface {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~LEDInterface() = default;

    /**
     * @brief Initialize the LED hardware.
     */
    void setup() override = 0;

    /**
     * @brief Main loop for updating LED state.
     */
    void loop() override = 0;

    /**
     * @brief Turn the LED red.
     */
    virtual void turnRed() = 0;

    /**
     * @brief Turn the LED green.
     */
    virtual void turnGreen() = 0;

    /**
     * @brief Turn the LED yellow.
     */
    virtual void turnYellow() = 0;

    /**
     * @brief Turn the LED blue.
     */
    virtual void turnBlue() = 0;

    /**
     * @brief Turn the LED off.
     */
    virtual void turnOff() = 0;
};
#endif