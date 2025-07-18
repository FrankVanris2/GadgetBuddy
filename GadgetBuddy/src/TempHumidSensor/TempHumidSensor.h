/**
 * By: Frank Vanris
 * Date: 7/18/2025
 * Desc: Implementing my dht11 sensor to read temperature and humidity
 */

 #pragma once

 #include "Interfaces/MachineComponentsInterface.h"
 #include "DHT.h"
 #include "CircularBuffer/CircularBuffer.h"

class TempHumidSensor : public MachineComponentsInterface {
public:
    /// @brief Constructor for my Temperature/Humidity Sensor (DHT11)
    /// @param DataPin The pin that connects to my DHT11 Sensor
    /// @param dht_type The type of DHT sensor that I have on hand
    /// @param dht_interval The interval that it takes to obtain specific information from the sensor itself.
    TempHumidSensor(int DataPin, int dht_type, unsigned long dht_interval);

    /// @brief setup function for the DHT11 sensor
    void setup() override;

    /// @brief loop function for the DHT11 sensor
    void loop() override;

    /// @brief Get the current Temperature
    /// @return Temperature Data
    int getTemperatureData() {
        return mTemperatureData;
    }

    /// @brief Get the current Humidity
    /// @return Humidity Data
    int getHumidityData() {
        return mHumidityData;
    }

private:
    DHT dht;
    CircularBuffer<int> tempAvgBuffer;
    CircularBuffer<int> humidityAvgBuffer;
    int mTemperatureData;
    int mHumidityData;
    unsigned long previousMillis;

    unsigned long DHT_INTERVAL;
    const int DATA_PIN;
    const int DHT_TYPE;

    /// @brief Obtaining the Temperature and Humidity Data from the
    /// DHT11 sensor.
    void obtainingTemperature_HumidityData();

    /// @brief Obtaining the Average of the temperature data.
    /// @param temp 
    /// @return averagedTemperature
    int averagingTempData(int temp);

    /// @brief Obtaining the Average of the humidity data.
    /// @param humidity 
    /// @return the averagedHumidity
    int averagingHumidData(int humidity);
};
