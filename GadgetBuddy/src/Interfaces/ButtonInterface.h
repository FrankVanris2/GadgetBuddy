/**
 * @file ButtonInterface.h
 * @author Frank Vanris
 * @date 7/20/2025
 * @brief Interface for button handling in GadgetBuddy.
 *
 * This abstract class defines the required methods for button implementations,
 * including debouncing logic for reliable user input.
 */

#ifndef BUTTON_INTERFACE_H
#define BUTTON_INTERFACE_H

#include "MachineComponentsInterface.h"

/**
 * @class ButtonInterface
 * @brief Abstract interface for button modules.
 */
class ButtonInterface : public MachineComponentsInterface {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~ButtonInterface() = default;

    /**
     * @brief Initialize the button hardware.
     */
    void setup() override = 0;

    /**
     * @brief Main loop for updating button states.
     */
    void loop() override = 0;

    /**
     * @brief Debounce logic for button input.
     * @param currentReading Current raw button reading.
     * @param currentTime Current timestamp.
     * @param lastRawState Reference to last raw state variable.
     * @param debouncedState Reference to debounced state variable.
     * @param lastDebounceTimer Reference to last debounce timer variable.
     * @param isLeftButton True if processing the left button, false for right.
     */
    virtual void processButtonDebounce(int currentReading, unsigned long currentTime,
                                       int& lastRawState, int& debouncedState,
                                       unsigned long& lastDebounceTimer,
                                       bool isLeftButton) = 0;
};

#endif