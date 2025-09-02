/**
 * @file LCDScreen.h
 * @author Frank Vanris
 * @date 7/5/2025
 * @brief LCD screen visualization class for GadgetBuddy.
 *
 * This class implements the LCD screen logic, enabling users to visually monitor
 * sensor data and device status. It uses the strategy pattern for dynamic screen
 * switching and integrates with all major hardware modules.
 */

#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H

#include <LiquidCrystal_I2C.h>
#include "LED/LED.h"
#include "Interfaces/LCDInterface.h"
#include "Interfaces/DisplayStrategy.h"
#include "Interfaces/ErrorReportingInterface.h"
#include "Buttons/Buttons.h"
#include "TempHumidSensor/TempHumidSensor.h"
#include "RTCClock/RTCClock.h"
#include "AirQuality/AirQuality.h"
#include "Compass/Compass.h"

/**
 * @class LCDScreen
 * @brief Handles visualization and screen management for GadgetBuddy.
 */
class LCDScreen : public LCDInterface {
public:
    /**
     * @brief Constructor.
     * @param led_ref Reference to LED module.
     * @param buttons_ref Reference to Buttons module.
     * @param temphumid_ref Reference to TempHumidSensor module.
     * @param rtcc_ref Reference to RTCClock module.
     * @param airqual_ref Reference to AirQuality module.
     * @param compass_ref Reference to Compass module.
     */
    LCDScreen(LED& led_ref, Buttons& buttons_ref, TempHumidSensor& temphumid_ref,
              RTCClock& rtcc_ref, AirQuality& airqual_ref, Compass& compass_ref);

    /**
     * @brief Destructor.
     */
    ~LCDScreen();

    /**
     * @brief Initialize the LCD screen and related modules.
     */
    void setup() override;

    /**
     * @brief Main loop for updating and displaying screen content.
     */
    void loop() override;

private:
    /**
     * @brief Update sensor data and display the current screen.
     */
    void updateAndDisplayScreen();

    /**
     * @brief Display an error screen with the provided message.
     * @param errorMessage Error message to display.
     */
    void displayErrorScreen(const char* errorMessage);

    /**
     * @brief Check for errors in connected modules.
     * @return Error message if any error is present, nullptr otherwise.
     */
    const char* checkForErrors();

    /**
     * @brief Get the current display strategy based on screen state.
     * @return Pointer to the current DisplayStrategy.
     */
    DisplayStrategy* getCurrentDisplayStrategy();

    /**
     * @brief Clean up the current display strategy instance.
     */
    void cleanupDisplayStrategy();

    LiquidCrystal_I2C lcd;         ///< LCD display instance
    int mCurrentScreenState;       ///< Current screen state index

    LED& mLedRef;                  ///< Reference to LED module
    Buttons& mButtonsRef;          ///< Reference to Buttons module
    TempHumidSensor& mTempHumidRef;///< Reference to TempHumidSensor module
    RTCClock& mRTCRef;             ///< Reference to RTCClock module
    AirQuality& mAirQualRef;       ///< Reference to AirQuality module
    Compass& mCompassRef;          ///< Reference to Compass module

    DisplayStrategy* mCurrentStrategy; ///< Pointer to current display strategy
    int mLastScreenState;              ///< Last screen state index

    unsigned long mLastUpdate;         ///< Last update timestamp
    static const unsigned long UPDATE_INTERVAL = 500; ///< Update interval (ms)
    bool mForceUpdate;                 ///< Force update flag
};

#endif
