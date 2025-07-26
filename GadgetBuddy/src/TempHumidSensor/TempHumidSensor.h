/**
 * By: Frank Vanris
 * Date: 7/18/2025
 * Desc: Implementing my dht11 sensor to read temperature and humidity
 */

 #ifndef TEMP_HUMID_SENSOR_H
 #define TEMP_HUMID_SENSOR_H

 #include "Interfaces/TempHumidInterface.h"
 #include "DHT.h"
 #include "CircularBuffer/CircularBuffer.h"

class TempHumidSensor : public TempHumidInterface {
public:
    /// @brief Constructor for my Temperature/Humidity Sensor (DHT11)
    /// @param DataPin The pin that connects to my DHT11 Sensor
    /// @param dht_type The type of DHT sensor that I have on hand
    /// @param dht_interval The interval that it takes to obtain specific information from the sensor itself.
    TempHumidSensor(int DataPin, int dht_type, unsigned long dhtInterval);

    /// @brief setup function for the DHT11 sensor
    void setup() override;

    /// @brief loop function for the DHT11 sensor
    void loop() override;

    /// @brief Get the current Temperature
    /// @return Temperature Data
    float getTemperatureData() {
        return mTemperatureData;
    }

    /// @brief Get the current Humidity
    /// @return Humidity Data
    float getHumidityData() {
        return mHumidityData;
    }

    /// @brief Obtaining Error if error occurs within DHT Sensor
    /// @return an error message for what broke
    const char* getErrorMessage() override;

private:
    const int DATA_PIN;
    const int DHT_TYPE;
    const unsigned long DHT_INTERVAL;

    DHT dht;

    CircularBuffer<float> tempAvgBuffer;
    CircularBuffer<float> humidityAvgBuffer;

    float mTemperatureData;
    float mHumidityData;
    bool mHasError;
    unsigned long previousMillis;

    /// @brief Obtaining the Temperature and Humidity Data from the
    /// DHT11 sensor.
    void obtainingTemperature_HumidityData() override;

    /// @brief Obtaining the Average of the temperature data.
    /// @param temp 
    /// @return averagedTemperature
    float averagingTempData(float temp) override;

    /// @brief Obtaining the Average of the humidity data.
    /// @param humidity 
    /// @return the averagedHumidity
    float averagingHumidData(float humidity) override;
};

#endif
