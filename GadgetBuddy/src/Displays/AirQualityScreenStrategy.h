/**
 * By: Frank Vanris
 * Date: 8/1/2025
 * Desc: Implementing the Air Quality Screen Strategy for the LCD Display
*/

#ifndef AIR_QUALITY_SCREEN_STRATEGY_H
#define AIR_QUALITY_SCREEN_STRATEGY_H

#include "Interfaces/DisplayStrategy.h"
#include "AirQuality/AirQuality.h"

class AirQualityScreenStrategy : public DisplayStrategy {
public:
    AirQualityScreenStrategy(AirQuality& sensor) : mSensorRef(sensor) {}

    void display(LiquidCrystal_I2C& lcd) override {
        lcd.setCursor(0,0);
        lcd.print("Air Quality:");
        
        lcd.setCursor(0,1);
        lcd.print("CO2 = ");
        lcd.print(mSensorRef.getAirQualityData(), 1);
        lcd.print(" PPM");
        
        lcd.setCursor(0,2);
        lcd.print("Status: ");
        lcd.print(mSensorRef.getAirQualityStatus());
    }

    const char* getScreenName() override {
        return "Air Quality Screen";
    }

private:
    AirQuality& mSensorRef;
};

#endif