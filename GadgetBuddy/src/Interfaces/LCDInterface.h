/**
 * @file LCDInterface.h
 * @author Frank Vanris
 * @date 7/20/2025
 * @brief Interface for LCD display modules in GadgetBuddy.
 *
 * This abstract class defines the required methods for LCD display implementations,
 * supporting modularity and enabling unit testing of display-related components.
 */

#ifndef LCD_INTERFACE_H
#define LCD_INTERFACE_H

#include "MachineComponentsInterface.h"

/**
 * @class LCDInterface
 * @brief Abstract interface for LCD display modules.
 */
class LCDInterface : public MachineComponentsInterface {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~LCDInterface() = default;

    /**
     * @brief Initialize the LCD display hardware.
     */
    void setup() override = 0;

    /**
     * @brief Main loop for updating the LCD display.
     */
    void loop() override = 0;
};

#endif