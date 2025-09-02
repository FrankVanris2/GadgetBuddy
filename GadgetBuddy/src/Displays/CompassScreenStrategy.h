/**
 * @file CompassScreenStrategy.h
 * @author Frank Vanris
 * @date 8/7/2025
 * @brief Strategy class for displaying compass information on the LCD.
 *
 * This class implements the logic for presenting compass direction, heading,
 * and axis readings on the LCD display using the Compass sensor module.
 */

#ifndef COMPASS_SCREEN_STRATEGY_H
#define COMPASS_SCREEN_STRATEGY_H

#include "Interfaces/DisplayStrategy.h"
#include "Compass/Compass.h"

class CompassScreenStrategy : public DisplayStrategy {
public:
    CompassScreenStrategy(Compass& compass) : mCompassRef(compass) {}

    void display(LiquidCrystal_I2C& lcd) override {
        lcd.setCursor(0,0);
        lcd.print(F("Compass: "));
        
        lcd.setCursor(0,1);
        lcd.print(F("Direction: "));
        lcd.print(mCompassRef.getDirection());

        lcd.setCursor(0,2);
        lcd.print(F("Heading: "));
        lcd.print(mCompassRef.getHeading());

        lcd.setCursor(0,3);
        lcd.print(F("X:"));
        lcd.print(mCompassRef.getX());
        lcd.print(F(" Y:"));
        lcd.print(mCompassRef.getY());
        lcd.print(F(" Z:"));
        lcd.print(mCompassRef.getZ());
    }

    const char* getScreenName() override {
        return "Compass Screen";
    }

private:
    Compass& mCompassRef;
};

#endif