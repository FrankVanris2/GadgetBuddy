/**
 * By: Frank Vanris
 * Date: 7/17/2025
 * Desc: Creating a Mock class around the DHT11 Sensor
 */

 #pragma once

class MockDHT {
public:

    // Initialization of the MockDHT class
    MockDHT(int pin, int type) : _pin(pin), _type(type) {}

    // Simulate begin method
    void begin() { _initialize = true; }

    // Simulate read temperature method
    float readTemperature() {
        return _simulateError ?  -1 : _mockTemp;
    }

    // Simulate read humidity method
    float readHumidity() {
        return _simulateError ? -1 : _mockHumidity;
    }

    // Test helper method
    void setMockValues(float temp, float humidity) {
        _mockTemp = temp;
        _mockHumidity = humidity;
        _simulateError = false;
    }

    void simulateError(bool error) { _simulateError = error; }


private:
    int _pin, _type;
    bool _initialize = false;
    bool _simulateError = false;
    float _mockTemp = 25.0f;
    float _mockHumidity = 60.0f;
};