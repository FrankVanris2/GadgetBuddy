/**
 * By: Frank Vanris
 * Date: 8/5/2025
 * Desc: Obtaining Air Quality Data to Display on the LCD Screen
*/

#include "AirQuality.h"
#include <Arduino.h>

const char* MQ_READ_ERROR_MSG = "MQ Read Error!";

AirQuality::AirQuality(int dataPin, unsigned long mq_interval) :
    DATA_PIN(dataPin),
    MQ_INTERVAL(mq_interval),
    previousMillis(0),
    mHasError(false),
    mAirQualityReading(0.0f)
{}

void AirQuality::setup() {
    Serial.println("Initializing MQ setup.");
}

void AirQuality::loop() {
    unsigned long currentMillis = millis();
    if((unsigned long) (currentMillis - previousMillis) >= MQ_INTERVAL) {
        previousMillis = currentMillis;

        int raw_adc_reading = analogRead(DATA_PIN);

        if(raw_adc_reading == 0 || raw_adc_reading == 1023) {
            mHasError = true; 
        } else {
            clearError();
            mAirQualityReading = static_cast<float>(raw_adc_reading);
        }
    }
}

const char* AirQuality::getErrorMessage() {
    if(hasError()) {
        return MQ_READ_ERROR_MSG;
    }
    return nullptr;
}