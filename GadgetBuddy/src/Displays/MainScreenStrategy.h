/**
 * @file MainScreenStrategy.h
 * @author Frank Vanris
 * @date 8/1/2025
 * @brief Strategy class for displaying the main screen interface on the LCD.
 *
 * This class implements the logic for presenting the main screen, including
 * date and time information, using the RTCClock module.
 */

#ifndef MAIN_SCREEN_STRATEGY_H
#define MAIN_SCREEN_STRATEGY_H

#include "Interfaces/DisplayStrategy.h"
#include "RTCClock/RTCClock.h"

class MainScreenStrategy : public DisplayStrategy {
public:
    MainScreenStrategy(RTCClock& rtc) : mRTCRef(rtc) {}

    void display(LiquidCrystal_I2C& lcd) override {
        lcd.setCursor(5,0);
        lcd.print(F("GadgetBuddy"));
        
        lcd.setCursor(0,1);
        lcd.print(F("Date: "));
        lcd.print(mRTCRef.getDate());

        lcd.setCursor(0,2);
        lcd.print(F("Time: "));
        lcd.print(mRTCRef.getTime());
    }

    const char* getScreenName() override {
        return "Main Screen";
    }

private:
    RTCClock& mRTCRef;
};

#endif