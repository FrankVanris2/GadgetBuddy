/**
 * By: Frank Vanris
 * Date: 8/7/2025
 * Desc: Creating a Compass class for the GadgetBuddy, a new screen state for project direction.
 */

#ifndef COMPASS_H
#define COMPASS_H

#include "Interfaces/CompassInterface.h"
#include "Interfaces/ErrorReportingInterface.h"
#include <QMC5883LCompass.h>

class Compass : public CompassInterface, public ErrorReportingInterface {
public:
    Compass();
    void setup() override;
    void loop() override;

    // CompassInterface methods
    int getHeading() const override;
    const char* getDirection() const override;
    int getX() const override;
    int getY() const override;
    int getZ() const override;

    // Error handling
    const char* getErrorMessage() override;
    bool hasError() override { return mHasError; }
    void clearError() override { mHasError = false; }

private:
    QMC5883LCompass mCompass;
    bool mHasError;
    char mDirection[4];

    // Cached readings
    int mX, mY, mZ, mHeading;

    // Helper methods
    void updateReadings();
    bool validateReadings();

};
#endif