/**
 * @file RTCClock.h
 * @author Frank Vanris
 * @date 7/30/2025
 * @brief RTCClock implementation for GadgetBuddy main screen time and date display.
 *
 * This class provides an interface to the RTC_DS1307 real-time clock, enabling
 * accurate time and date tracking for the device. It supports error reporting
 * and integrates with the main screen logic.
 */

#ifndef RTCCLOCK_H
#define RTCCLOCK_H

#include <RTClib.h>
#include <Arduino.h>
#include "Interfaces/RTCInterface.h"
#include "Interfaces/ErrorReportingInterface.h"

/**
 * @class RTCClock
 * @brief Handles RTC time and date functionality for GadgetBuddy.
 */
class RTCClock : public RTCInterface, public ErrorReportingInterface {
public:
    /**
     * @brief Constructor.
     */
    RTCClock();

    /**
     * @brief Initialize the RTC hardware.
     */
    void setup() override;

    /**
     * @brief Main loop for updating RTC state.
     */
    void loop() override;

    /**
     * @brief Get the current date as a string.
     * @return Date string.
     */
    String getDate() { return mDateData; }

    /**
     * @brief Get the current time as a string.
     * @return Time string. Time is in military format.
     */
    String getTime() { return mTimeData; }

    // ErrorReportingInterface methods

    /**
     * @brief Get the latest error message.
     * @return Error message string.
     */
    const char* getErrorMessage() override;

    /**
     * @brief Check if the RTC is currently in an error state.
     * @return True if error present, false otherwise.
     */
    bool hasError() override { return mHasError; }

    /**
     * @brief Clear the current error state.
     */
    void clearError() override { mHasError = false; }

private:
    RTC_DS1307 rtc;        ///< RTC hardware instance
    bool mHasError;        ///< Error state flag

    String mTimeData;      ///< Cached time string
    String mDateData;      ///< Cached date string

    /**
     * @brief Record the current date and time from the RTC.
     */
    void recordDateAndTime();

    /**
     * @brief Check if the device is connected to a computer.
     * @return True if connected, false otherwise.
     */
    bool isConnectedToComputer();
};

#endif //