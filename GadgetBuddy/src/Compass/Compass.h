/**
 * By: Frank Vanris
 * Date: 8/7/2025
 * Desc: Creating a Compass class for the GadgetBuddy, a new screen state for project direction.
 */

#ifndef COMPASS_H
#define COMPASS_H

#include "Interfaces/CompassInterface.h"
#include "Interfaces/ErrorReportingInterface.h"

class Compass : public CompassInterface, public ErrorReportingInterface {
public:
    Compass();
    void setup() override;
    void loop() override;

    // Error handling
    const char* getErrorMessage() override;
    bool hasError() override { return mHasError; }
    void clearError() override { mHasError = false; }

private:
    bool mHasError;
};
#endif