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

    float getAirQualityData() const { return mAirQualityReading; }
    float getCO2_PPM() const { return mCO2_PPM; }
    // ErrorReportingInterface methods
    const char* getErrorMessage() override;
    bool hasError() override { return mHasError; }
    void clearError() override { mHasError = false; }

private:
    const int DATA_PIN;
    const unsigned long MQ_INTERVAL;
    unsigned long previousMillis;
    bool mHasError;

    float mAirQualityReading;
    float mCO2_PPM;

    float calculatePPM(int adcReading);

};
#endif