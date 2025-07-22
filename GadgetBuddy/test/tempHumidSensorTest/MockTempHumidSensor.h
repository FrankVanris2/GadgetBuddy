/**
 * By: Frank Vanris
 * Date: 7/22/2025
 * Desc: Mocking the TempHumidSensor class for testing purposes
 */

#pragma once
#include "../mocks/MockDHT.h"
#include "../circularBufferTest/MockCircularBuffer.h"
#include <unity.h>

class MockTempHumidSensor {
public:
    MockTempHumidSensor(int dataPin, int dht_type) :
        DATA_PIN(dataPin),
        DHT_TYPE(dht_type),
        dht(DATA_PIN, DHT_TYPE),
        tempAvgBuffer(10),
        humidityAvgBuffer(10),
        mTemperatureData(0.0f),
        mHumidityData(0.0f),
        mHasError(false)
    {}

    void setup() {
        dht.begin();

    }

    void obtainingTemperature_HumidityData() {
        float humidity = dht.readHumidity();
        float temp = dht.readTemperature();

        if((temp == -1.0f || humidity == -1.0f) ||isnan(temp) || isnan(humidity)) {
            mHasError = true;
        } else {
            mHasError = false;
            mTemperatureData = averagingTempData(temp);
            mHumidityData = averagingHumidData(humidity);
        }
    }

    float getTemperatureData() { return mTemperatureData; }
    float getHumidityData() { return mHumidityData; }
    bool hasError() { return mHasError; }

    // Test helper to access DHT mock
    MockDHT& getDHTMock() { return dht; }

private: 
    const int DATA_PIN;
    const int DHT_TYPE;
    MockDHT dht;
    MockCircularBuffer<float> tempAvgBuffer;
    MockCircularBuffer<float> humidityAvgBuffer;
    float mTemperatureData;
    float mHumidityData;
    bool mHasError;

    // Helper functions for averaging data
    float averagingTempData(float temp) {
        tempAvgBuffer.push_back(temp);
        if(tempAvgBuffer.isEmpty()) {
            return 0.0f;
        }
        return tempAvgBuffer.sum() / tempAvgBuffer.size();
    }

    float averagingHumidData(float humidity) {
        humidityAvgBuffer.push_back(humidity);
        if(humidityAvgBuffer.isEmpty()) {
            return 0.0f;
        }
        return humidityAvgBuffer.sum() / humidityAvgBuffer.size();
    }
};