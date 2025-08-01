/**
 * By: Frank Vanris
 * Date: 8/01/2025
 * Desc: Interface for Display Strategy
 */

 #ifndef DISPLAY_STRATEGY_H
 #define DISPLAY_STRATEGY_H

#include <LiquidCrystal_I2C.h>

class DisplayStrategy {
public:
    virtual ~DisplayStrategy() = default;
    virtual void display(LiquidCrystal_I2C& lcd) = 0;
    virtual const char* getScreenName() = 0;
};
 #endif