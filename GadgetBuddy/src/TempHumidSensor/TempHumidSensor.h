/**
 * @file TempHumidSensor.h
 * @author Frank Vanris
 * @date 7/18/2025
 * @brief DHT11 temperature and humidity sensor implementation for GadgetBuddy.
 *
 * This class interfaces with the DHT11 sensor to read temperature and humidity data,
 * provides averaging using a circular buffer, and supports error reporting for reliable operation.
 */

#ifndef TEMP_HUMID_SENSOR_H
#define TEMP_HUMID_SENSOR_H

#include "Interfaces/TempHumidInterface.h"
#include "Interfaces/ErrorReportingInterface.h"
#include "DHT.h"
#include "CircularBuffer/CircularBuffer.h"

/**
 * @class TempHumidSensor
 * @brief Handles DHT11 temperature and humidity readings, averaging, and error reporting.
 */
class TempHumidSensor : public TempHumidInterface, public ErrorReportingInterface {
public:
    /**
     * @brief Constructor for Temperature/Humidity Sensor (DHT11).
     * @param DataPin The pin that connects to the DHT11 Sensor.
     * @param dht_type The type of DHT sensor in use.
     * @param dht_interval The interval for obtaining sensor data.
     */
    TempHumidSensor(int DataPin, int dht_type, unsigned long dhtInterval);

    /**
     * @brief Initialize the DHT11 sensor hardware.
     */
    void setup() override;

    /**
     * @brief Main loop for updating sensor readings.
     */
    void loop() override;

    /**
     * @brief Get the current temperature reading.
     * @return Temperature value.
     */
    float getTemperatureData() {
        return mTemperatureData;
    }

    /**
     * @brief Get the current humidity reading.
     * @return Humidity value.
     */
    float getHumidityData() {
        return mHumidityData;
    }

    // ErrorReportingInterface methods

    /**
     * @brief Get the latest error message.
     * @return Error message string.
     */
    const char* getErrorMessage() override;

    /**
     * @brief Check if the sensor is currently in an error state.
     * @return True if error present, false otherwise.
     */
    bool hasError() override { return mHasError; }

    /**
     * @brief Clear the current error state.
     */
    void clearError() override { mHasError = false; }

private:
    const int DATA_PIN;                ///< Pin for DHT11 sensor
    const int DHT_TYPE;                ///< DHT sensor type
    const unsigned long DHT_INTERVAL;  ///< Interval for sensor readings

    DHT dht;                           ///< DHT sensor instance

    CircularBuffer<float> tempAvgBuffer;     ///< Buffer for temperature averaging
    CircularBuffer<float> humidityAvgBuffer; ///< Buffer for humidity averaging

    float mTemperatureData;            ///< Latest temperature value
    float mHumidityData;               ///< Latest humidity value
    bool mHasError;                    ///< Error state flag
    unsigned long previousMillis;      ///< Last reading timestamp

    /**
     * @brief Obtain temperature and humidity data from the DHT11 sensor.
     */
    void obtainingTemperature_HumidityData() override;

    /**
     * @brief Calculate the average of temperature data.
     * @param temp Temperature value to include.
     * @return Averaged temperature.
     */
    float averagingTempData(float temp) override;

    /**
     * @brief Calculate the average of humidity data.
     * @param humidity Humidity value to include.
     * @return Averaged humidity.
     */
    float averagingHumidData(float humidity) override;
};

#endif
