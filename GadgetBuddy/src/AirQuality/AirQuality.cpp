/**
 * By: Frank Vanris
 * Date: 8/5/2025
 * Desc: Obtaining Air Quality Data to Display on the LCD Screen
*/

#include "AirQuality.h"
#include <Arduino.h>

const char* MQ_READ_ERROR_MSG = "MQ Read Error!";

const float AirQuality::LOAD_RESISTANCE = 1000.0f; // 1k ohm load resistor
const float AirQuality::CLEAN_AIR_RATIO = 3.6f; // Rs/R0 ratio in clean air
const float AirQuality::CO2_CURVE_A = 110.47f; // Curve coefficient A
const float AirQuality::CO2_CURVE_B = -2.862f; // Curve coefficient B
const float AirQuality::VOLTAGE_SUPPLY = 5.0f; // Arduino supply voltage

AirQuality::AirQuality(int dataPin, unsigned long mq_interval) :
    DATA_PIN(dataPin),
    MQ_INTERVAL(mq_interval),
    previousMillis(0),
    mHasError(false),
    mRawADCReading(0.0f),
    mCO2_PPM(400.0f),
    mR0(7600.0f) // Reduced R0 for 1k load resistor (was 76000)
{}

void AirQuality::setup() {
    Serial.println("Initializing Air Quality setup.");
}

void AirQuality::loop() {
    unsigned long currentMillis = millis();
    if((unsigned long) (currentMillis - previousMillis) >= MQ_INTERVAL) {
        previousMillis = currentMillis;
        performSensorReading();
    }
}

void AirQuality::performSensorReading() {
    // Read raw ADC value
    int rawADC = analogRead(DATA_PIN);
    mRawADCReading = static_cast<float>(rawADC);

    // Check for sensor connection issues
    if(rawADC == 0 || rawADC >= 1023) {
        updateErrorState(true);
        mCO2_PPM = 0.0f;
        return;
    }

    // Calculate PPM from ADC reading
    float calculatedPPM = calculatePPM(rawADC);

    // Validate the reading
    if(validateSensorReading(calculatedPPM)) {
        mCO2_PPM = calculatedPPM;
        updateErrorState(false);
    } else {
        updateErrorState(true);
    }
}

float AirQuality::calculatePPM(int adcReading) {
    float sensorResistance = calculateResistance(adcReading);

    // Calculate Rs/R0 ratio
    float ratio = sensorResistance / mR0;

    // Ensure ratio is within reasonable bounds
    if (ratio <= 0) {
        return 0.0f;
    }

    // Calculate PPM using MQ-135 CO2 curve: PPM = A * pow(ratio, B)
    float ppm = CO2_CURVE_A * pow(ratio, CO2_CURVE_B);
    
    // Clamp to reasonable values for corrected sensor - lowered minimum
    if (ppm < 1.0f) ppm = 1.0f;
    if (ppm > 10000.0f) ppm = 10000.0f;

    return ppm;
}

float AirQuality::calculateResistance(int adcReading) {
    float voltage = (static_cast<float>(adcReading) / 1024.0f) * VOLTAGE_SUPPLY;
    
    // Avoid division by zero
    if (voltage <= 0.01f) {
        voltage = 0.01f;
    }

    // Calculate sensor resistance using voltage divider: Rs = ((Vcc - V) / V) * Rl
    float resistance = ((VOLTAGE_SUPPLY - voltage) / voltage) * LOAD_RESISTANCE;
    return resistance;
}

bool AirQuality::validateSensorReading(float ppmValue) {
    // Check for invalid readings
    if(isnan(ppmValue) || isinf(ppmValue)) {
        return false;
    }

    // Check for reasonable CO2 range (1 ppm to 10,000 ppm) - lowered minimum
    if(ppmValue < 1.0f || ppmValue > 10000.0f) {
        return false;
    }
    return true;
}

void AirQuality::updateErrorState(bool hasError) {
    if (hasError) {
        mHasError = true;
    } else {
        clearError();
    }
}

const char* AirQuality::getAirQualityStatus() const {
    if(mHasError) return "ERROR";

    // CO2 levels classification - adjusted for actual sensor readings
    if(mCO2_PPM < 3) return "EXCELLENT";
    else if(mCO2_PPM < 5) return "VERY GOOD";
    else if(mCO2_PPM < 8) return "GOOD";
    else if(mCO2_PPM < 15) return "FAIR";
    else if(mCO2_PPM < 25) return "POOR";
    else if (mCO2_PPM < 50) return "BAD";
    else return "HAZARDOUS";
}

const char* AirQuality::getErrorMessage() {
    if (!hasError()) {
        return nullptr;
    }

    return MQ_READ_ERROR_MSG;
}