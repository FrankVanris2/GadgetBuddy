/**
 * By: Frank Vanris
 * Date: 8/2/2025
 * Desc: Implementing the Radio Screen Strategy for the LCD Display
*/

#ifndef RADIO_SCREEN_STRATEGY_H
#define RADIO_SCREEN_STRATEGY_H

#include "Interfaces/DisplayStrategy.h"

class RadioScreenStrategy : public DisplayStrategy {
public:
    RadioScreenStrategy() {}

    void display(LiquidCrystal_I2C& lcd) override {
        lcd.setCursor(0, 0);
        lcd.print(F("Radio Station:"));
        
        lcd.setCursor(0, 1);
        lcd.print(F("To be added ..."));
    }

    const char* getScreenName() override {
        return "Radio Screen";
    }

private:
};
#endif