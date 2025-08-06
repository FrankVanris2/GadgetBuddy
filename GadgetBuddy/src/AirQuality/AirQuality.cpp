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
    mAirQualityReading(0.0f),
    mCO2_PPM(0.0f),
    mR0(0.0f)
{}

void AirQuality::setup() {
    Serial.println("Initializing MQ setup.");
    // IMPORTANT: the MQ sensor requires a burn-in period of up to 24-48 hours. It's best
    // to keep it running during this period before calibrating.
    // Call calibrateR0() after the burn-in period to set the R0 value;
    // Call calibrateR0(); in GadgetBuddy::setup() AFTER burn-in.
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

            // Manual PPM calculation
            mCO2_PPM = calculatePPM(raw_adc_reading);
        }
    }
}

float AirQuality::calculatePPM(int adcReading) {
    // Convert ADC to voltage
    float voltage = (adcReading / 1023.0) * 5.0;

    // Calculate sensor resistance
    float sensorResistance = ((5.0 - voltage) / voltage) * 10000; // Assuming a 10k load resistor

    // Calculate ratio (Rs/R0)
    // R0 should be calibrated in clean air (around 76000 ohms for MQ135)
    float R0 = 76000.0;
    float ratio = sensorResistance / R0;

    // MQ135 CO2 curve: PPM = 110.47 * pow(ratio, -2.862)
    float ppm = 110.47 * pow(ratio, -2.862);
    return ppm;
}

const char* AirQuality::getErrorMessage() {
    if(hasError()) {
        return MQ_READ_ERROR_MSG;
    }
    return nullptr;
}