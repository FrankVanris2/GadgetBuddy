/**
 * By: Frank Vanris
 * Date: 8/1/2025
 * Desc: Creating the Main Screen Interface for the Display
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
        lcd.print("GadgetBuddy");
        
        lcd.setCursor(0,1);
        lcd.print("Date: ");
        lcd.print(mRTCRef.getDate());

        lcd.setCursor(0,2);
        lcd.print("Time: ");
        lcd.print(mRTCRef.getTime());
    }

    const char* getScreenName() override {
        return "Main Screen";
    }

private:
    RTCClock& mRTCRef;
};

#endif