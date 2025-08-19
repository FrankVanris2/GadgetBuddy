/**
 * By: Frank Vanris
 * Date: 8/2/2025
 * Desc: Implementing the Radio Screen Strategy for the LCD Display
*/

#ifndef RADIO_SCREEN_STRATEGY_H
#define RADIO_SCREEN_STRATEGY_H

#include "Interfaces/DisplayStrategy.h"
#include "Radio/Radio.h"

class RadioScreenStrategy : public DisplayStrategy {
public:
    RadioScreenStrategy(Radio& radio) : mRadioRef(radio) {}

    void display(LiquidCrystal_I2C& lcd) override {
        lcd.setCursor(0,0);
        lcd.print(F("Radio Station:"));

        lcd.setCursor(0,1);
        lcd.print(mRadioRef.getStationName());

        lcd.setCursor(0,2);
        lcd.print(F("Frequency: "));
        lcd.print(mRadioRef.getFrequency(), 1);
        lcd.print(F("MHz"));
        
        lcd.setCursor(0,3);
        if (mRadioRef.isMuted()) {
            lcd.print(F("Status: MUTED"));
        } else {
            lcd.print(F("Status: PLAYING"));
        }
    }

    const char* getScreenName() override {
        return "Radio Screen";
    }

   
private:
    Radio& mRadioRef;
};

#endif