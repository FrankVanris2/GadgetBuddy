/**
 * @file DisplayStrategy.h
 * @author Frank Vanris
 * @date 8/01/2025
 * @brief Interface for LCD display screen strategies in GadgetBuddy.
 *
 * This abstract class defines the required methods for implementing different
 * display strategies, enabling modular and extensible screen management.
 */

#ifndef DISPLAY_STRATEGY_H
#define DISPLAY_STRATEGY_H

#include <LiquidCrystal_I2C.h>

/**
 * @class DisplayStrategy
 * @brief Abstract interface for LCD display screen strategies.
 */
class DisplayStrategy {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~DisplayStrategy() = default;

    /**
     * @brief Display the screen content on the provided LCD.
     * @param lcd Reference to the LiquidCrystal_I2C display.
     */
    virtual void display(LiquidCrystal_I2C& lcd) = 0;

    /**
     * @brief Get the name of the screen.
     * @return Screen name string.
     */
    virtual const char* getScreenName() = 0;
};
#endif