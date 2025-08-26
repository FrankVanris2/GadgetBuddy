/**
 * By: Frank Vanris
 * Date: 8/26/2025
 * Desc: Mocking the AirQuality sensor functions
*/

#pragma once

#include "Interfaces/AirQualityInterface.h"
#include <math.h>

class MockAirQuality : public AirQualityInterface {
public:
    MockAirQuality() : mCO2_PPM(400.0f), mRawADCReading(512.0f), mR0(7600.0f), mHasError(false), mIsWarmedUp(true) {}

    void setup() override {}
    void loop() override {}

    float getAirQualityData() const override { return mCO2_PPM; }
    float getRawADCReading() const override { return mRawADCReading; }
    float getR0Value() const override { return mR0; }

    // Pure logic methods
    float calculateResistance(int adcReading) {
        float voltage = adcReading * (5.0f / 1023.0f);
        if (voltage <= 0.01f) voltage = 0.01f;
        return ((5.0f - voltage) / voltage) * 1000.0f;
    }

    float calculatePPM(int adcReading) {
        float sensorResistance = calculateResistance(adcReading);
        float ratio = sensorResistance / mR0;
        if (ratio <= 0) return 0.0f;
        float ppm = 110.47f * pow(ratio, -2.862f);
        if (ppm < 1.0f) ppm = 1.0f;
        if (ppm > 10000.0f) ppm = 10000.0f;
        return ppm;
    }

    bool validateSensorReading(float ppmValue) {
        if(isnan(ppmValue) || isinf(ppmValue)) return false;
        if(ppmValue < 1.0f || ppmValue > 10000.0f) return false;
        return true;
    }

    const char* getAirQualityStatus() const {
        if(mHasError) return "ERROR  ";
        if(!mIsWarmedUp) return "WARM UP  ";
        if(mCO2_PPM < 25) return "EXCELLENT";
        else if(mCO2_PPM < 30) return "VERY GOOD";
        else if(mCO2_PPM < 40) return "GOOD     ";
        else if(mCO2_PPM < 50) return "FAIR";
        else if(mCO2_PPM < 60) return "POOR";
        else if (mCO2_PPM < 70) return "BAD      ";
        else return "HAZARDOUS";
    }

    // You can add error reporting methods if needed
    bool hasError() const { return mHasError; }
    void setError(bool err) { mHasError = err; }
    void setWarmedUp(bool warm) { mIsWarmedUp = warm; }
    void setCO2(float val) { mCO2_PPM = val; }

private:
    float mCO2_PPM;
    float mRawADCReading;
    float mR0;
    bool mHasError;
    bool mIsWarmedUp;
};