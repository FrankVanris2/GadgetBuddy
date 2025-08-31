/**
 * By: Frank Vanris
 * Date: 8/5/2025
 * Desc: Obtaining Air Quality readings so that they can be displayed on the LCD Screen
*/

#ifndef AIR_QUALITY_H
#define AIR_QUALITY_H

#include "Interfaces/AirQualityInterface.h"
#include "Interfaces/ErrorReportingInterface.h"

class AirQuality : public AirQualityInterface, public ErrorReportingInterface {
public:
    AirQuality(int dataPin, unsigned long mq_interval);

    void setup() override;
    void loop() override;

    float getAirQualityData() const override { return mCO2_PPM; }
    float getRawADCReading() const override { return mRawADCReading; }
    float getR0Value() const override{ return mR0; }
    float getCO2PPMValue() const override { return mCO2_PPM; }

    // Additional methods for better user experience
    const char* getAirQualityStatus() const;

    // Calculations and validations needed
    float calculatePPM(int adcReading);
    bool validateSensorReading(float ppmValue);
    float calculateResistance(int adcReading);
    
    // ErrorReportingInterface methods
    const char* getErrorMessage() override;
    bool hasError() override { return mHasError; }
    void clearError() override { mHasError = false; }

private:
    const int DATA_PIN;
    const unsigned long MQ_INTERVAL;
    unsigned long previousMillis;
    bool mHasError;

    float mRawADCReading;
    float mCO2_PPM;
    float mR0;
    
    // Warmup period variables
    unsigned long mWarmupStartTime;
    bool mIsWarmedUp;

    // MQ135 calculation constants
    static const float LOAD_RESISTANCE; // 10k ohm load resistor
    static const float CLEAN_AIR_RATIO; // Rs/R0 ratio in clean air
    static const float CO2_CURVE_A; // Curve coefficient A
    static const float CO2_CURVE_B; // Curve coefficient B
    static const float VOLTAGE_SUPPLY; // Arduino supply voltage

    // Private helpers
    void performSensorReading();
    void updateErrorState(bool hasError);
    
};
#endif