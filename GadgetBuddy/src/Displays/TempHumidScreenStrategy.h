/**
 * By: Frank Vanris
 * Date: 8/1/2025
 * Desc: Dislaying the Temperature and Humidity Screen
*/

#ifndef TEMP_HUMID_SCREEN_STRATEGY_H
#define TEMP_HUMID_SCREEN_STRATEGY_H

#include "Interfaces/DisplayStrategy.h"
#include "TempHumidSensor/TempHumidSensor.h"

class TempHumidScreenStrategy : public DisplayStrategy {
public:
    TempHumidScreenStrategy(TempHumidSensor& sensor) : mSensorRef(sensor) {}

    void display(LiquidCrystal_I2C& lcd) override {
        lcd.setCursor(0,0);
        lcd.print("Temp/Humid Screen:");

        lcd.setCursor(0,1);
        lcd.print("Temp: ");
        lcd.print(mSensorRef.getTemperatureData());
        lcd.print(" C");

        lcd.setCursor(0,2);
        lcd.print("Humidity: ");
        lcd.print(mSensorRef.getHumidityData());
        lcd.print(" %");
    }

    const char* getScreenName() override {
        return "Temperature/Humidity";
    }

private:
    TempHumidSensor& mSensorRef;
};

#endif
