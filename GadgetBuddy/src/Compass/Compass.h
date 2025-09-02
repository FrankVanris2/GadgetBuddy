/**
 * @file Compass.h
 * @author Frank Vanris
 * @date 8/7/2025
 * @brief Compass class for GadgetBuddy, providing directional readings and error handling.
 *
 * This class interfaces with the QMC5883L compass sensor to provide heading, direction,
 * and axis readings. It includes error reporting and validation for reliable operation.
 */

#ifndef COMPASS_H
#define COMPASS_H

#include "Interfaces/CompassInterface.h"
#include "Interfaces/ErrorReportingInterface.h"
#include <QMC5883LCompass.h>

/**
 * @class Compass
 * @brief Handles compass sensor readings and provides directional data.
 */
class Compass : public CompassInterface, public ErrorReportingInterface {
public:
    /**
     * @brief Constructor for Compass.
     */
    Compass();

    /**
     * @brief Initializes the compass sensor and internal state.
     */
    void setup() override;

    /**
     * @brief Main loop for updating compass readings.
     */
    void loop() override;

    // CompassInterface methods

    /**
     * @brief Get the current heading in degrees.
     * @return Heading value (0-359).
     */
    int getHeading() const override;

    /**
     * @brief Get the cardinal direction as a string (e.g., "N", "NE").
     * @return Direction string.
     */
    const char* getDirection() const override;

    /**
     * @brief Get the X-axis reading from the compass sensor.
     * @return X-axis value.
     */
    int getX() const override;

    /**
     * @brief Get the Y-axis reading from the compass sensor.
     * @return Y-axis value.
     */
    int getY() const override;

    /**
     * @brief Get the Z-axis reading from the compass sensor.
     * @return Z-axis value.
     */
    int getZ() const override;

    // ErrorReportingInterface methods

    /**
     * @brief Get the latest error message, if any.
     * @return Error message string.
     */
    const char* getErrorMessage() override;

    /**
     * @brief Check if the compass is currently in an error state.
     * @return True if error present, false otherwise.
     */
    bool hasError() override { return mHasError; }

    /**
     * @brief Clear the current error state.
     */
    void clearError() override { mHasError = false; }

private:
    QMC5883LCompass mCompass; ///< QMC5883L compass sensor instance
    bool mHasError;           ///< Error state flag
    char mDirection[4];       ///< Cardinal direction string

    // Cached readings
    int mX, mY, mZ, mHeading;

    /**
     * @brief Update compass readings and cache values.
     */
    void updateReadings();

    /**
     * @brief Validate compass readings for reliability.
     * @return True if readings are valid, false otherwise.
     */
    bool validateReadings();
};
#endif