/**
 * @file AirQuality.h
 * @author Frank Vanris
 * @date 8/5/2025
 * @brief AirQuality sensor interface for obtaining and processing air quality readings.
 *
 * This class provides functionality to read, process, and validate air quality data
 * from an MQ135 sensor, and exposes relevant information for display and error reporting.
 */

#ifndef AIR_QUALITY_H
#define AIR_QUALITY_H

#include "Interfaces/AirQualityInterface.h"
#include "Interfaces/ErrorReportingInterface.h"

/**
 * @class AirQuality
 * @brief Handles air quality readings and processing from an MQ135 sensor.
 */
class AirQuality : public AirQualityInterface, public ErrorReportingInterface {
public:
    /**
     * @brief Constructor for AirQuality.
     * @param dataPin The analog pin connected to the MQ135 sensor.
     * @param mq_interval The interval (ms) between sensor readings.
     */
    AirQuality(int dataPin, unsigned long mq_interval);

    /**
     * @brief Initializes the sensor and internal state.
     */
    void setup() override;

    /**
     * @brief Main loop for updating sensor readings and internal state.
     */
    void loop() override;

    /**
     * @brief Get the latest calculated CO2 PPM value.
     * @return The CO2 concentration in PPM.
     */
    float getAirQualityData() const override;

    /**
     * @brief Get the latest raw ADC reading from the sensor.
     * @return The raw ADC value.
     */
    float getRawADCReading() const override;

    /**
     * @brief Get the calculated R0 value (sensor baseline resistance).
     * @return The R0 value.
     */
    float getR0Value() const override;

    /**
     * @brief Get a human-readable air quality status string.
     * @return Status string ("EXCELLENT", "GOOD", "ERROR", etc.).
     */
    const char* getAirQualityStatus() const;

    /**
     * @brief Calculate the CO2 PPM value from an ADC reading.
     * @param adcReading The raw ADC value.
     * @return The calculated CO2 concentration in PPM.
     */
    float calculatePPM(int adcReading);

    /**
     * @brief Validate a calculated PPM value.
     * @param ppmValue The PPM value to validate.
     * @return True if valid, false otherwise.
     */
    bool validateSensorReading(float ppmValue);

    /**
     * @brief Calculate the sensor resistance from an ADC reading.
     * @param adcReading The raw ADC value.
     * @return The calculated resistance in ohms.
     */
    float calculateResistance(int adcReading);

    // ErrorReportingInterface methods

    /**
     * @brief Get the latest error message, if any.
     * @return Error message string.
     */
    const char* getErrorMessage() override;

    /**
     * @brief Check if the sensor is currently in an error state.
     * @return True if error present, false otherwise.
     */
    bool hasError() override;

    /**
     * @brief Clear the current error state.
     */
    void clearError() override;

private:
    // Configuration
    const int DATA_PIN;                ///< Analog pin for MQ135 sensor
    const unsigned long MQ_INTERVAL;   ///< Interval between readings (ms)

    // State
    unsigned long previousMillis;      ///< Last reading timestamp
    bool mHasError;                    ///< Error state flag

    float mRawADCReading;              ///< Last raw ADC value
    float mCO2_PPM;                    ///< Last calculated CO2 PPM
    float mR0;                         ///< Sensor baseline resistance

    // Warmup period
    unsigned long mWarmupStartTime;    ///< Warmup start timestamp
    bool mIsWarmedUp;                  ///< Warmup completion flag

    // MQ135 calculation constants
    static const float LOAD_RESISTANCE; ///< Load resistor value (ohms)
    static const float CLEAN_AIR_RATIO; ///< Rs/R0 ratio in clean air
    static const float CO2_CURVE_A;     ///< CO2 curve coefficient A
    static const float CO2_CURVE_B;     ///< CO2 curve coefficient B
    static const float VOLTAGE_SUPPLY;  ///< Supply voltage (V)

    // Private helpers

    /**
     * @brief Perform a sensor reading and update internal state.
     */
    void performSensorReading();

    /**
     * @brief Update the error state and message.
     * @param hasError True to set error, false to clear.
     */
    void updateErrorState(bool hasError);
};

#endif