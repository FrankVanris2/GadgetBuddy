/**
 * By: Frank Vanris
 * Date: 8/7/2025
 * Desc: Strategy for displaying the compass screen.
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
        lcd.print(F("To Be Added..."));
    }

    const char* getScreenName() override {
        return "Compass Screen";
    }

private:
    Compass& mCompassRef;
};

#endif