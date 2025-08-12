/**
 * By: Frank Vanris
 * Date: 8/12/2025
 * Desc: Creating a Radio class that implements the RadioInterface.
*/

#ifndef RADIO_H
#define RADIO_H
#include "Interfaces/RadioInterface.h"
#include "Interfaces/ErrorReportingInterface.h"

class Radio : public RadioInterface, public ErrorReportingInterface {
public:
    Radio();

    void setup() override;
    void loop() override;

    // ErrorReportingInterface implementation
    const char* getErrorMessage() override;
    bool hasError() override { return mHasError; }
    void clearError() override { mHasError = false; }

private:
    bool mHasError;
};

#endif