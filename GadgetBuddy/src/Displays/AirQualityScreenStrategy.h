/**
 * @file AirQualityScreenStrategy.h
 * @author Frank Vanris
 * @date 8/1/2025
 * @brief Strategy class for displaying air quality information on the LCD.
 *
 * This class implements the logic for presenting air quality status and PPM readings
 * on the LCD display using the AirQuality sensor module.
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
        lcd.print(F("Air Quality:"));
        
        lcd.setCursor(0,1);
        lcd.print(F("Status: "));
        lcd.print(mSensorRef.getAirQualityStatus());
        
        lcd.setCursor(0,2);
        lcd.print(F("PPM: "));
        lcd.print(mSensorRef.getAirQualityData(), 1);
    }

    const char* getScreenName() override {
        return "Air Quality Screen";
    }

private:
    AirQuality& mSensorRef;
};

#endif