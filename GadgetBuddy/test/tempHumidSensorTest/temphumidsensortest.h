/**
 * By: Frank Vanris
 * Date: 7/22/2025
 * Desc: Creating unit tests around the Mock DHT11 sensor module
 */

 #pragma once
 #include <unity.h>
 #include "MockTempHumidSensor.h"
 
 void test_sensor_initialization(void) {
    TEST_MESSAGE("Test: Sensor Initialization");
    MockTempHumidSensor sensor(11, 11);
    sensor.setup();

    TEST_ASSERT_EQUAL(0.0f, sensor.getTemperatureData());
    TEST_ASSERT_EQUAL(0.0f, sensor.getHumidityData());
    TEST_ASSERT_FALSE(sensor.hasError());
 }

 void test_sensor_normal_reading(void) {
    TEST_MESSAGE("Test: Normal sensor reading");
    MockTempHumidSensor sensor(11, 11);
    sensor.setup();

    // Set mock values
    sensor.getDHTMock().setMockValues(25.0f, 65.0f);

    sensor.obtainingTemperature_HumidityData();

    TEST_ASSERT_EQUAL(25.0f, sensor.getTemperatureData());
    TEST_ASSERT_EQUAL(65.0f, sensor.getHumidityData());
    TEST_ASSERT_FALSE(sensor.hasError());
 }

 void test_sensor_error_handling(void) {
    TEST_MESSAGE("Test: Sensor error handling");
    MockTempHumidSensor sensor(11, 11);
    sensor.setup();

    // Simulate an error
    sensor.getDHTMock().simulateError(true);

    sensor.obtainingTemperature_HumidityData();

    TEST_ASSERT_TRUE(sensor.hasError());
 }

 void test_sensor_averaging(void) {
    TEST_MESSAGE("Test: Sensor data averaging");
    MockTempHumidSensor sensor(11, 11);
    sensor.setup();

    // Add multiple readings
    sensor.getDHTMock().setMockValues(20.0f, 50.0f);
    sensor.obtainingTemperature_HumidityData();

    sensor.getDHTMock().setMockValues(30.0f, 70.0f);
    sensor.obtainingTemperature_HumidityData();

    // Should average to 25.0f and 60.0f
    TEST_ASSERT_EQUAL(25.0f, sensor.getTemperatureData());
    TEST_ASSERT_EQUAL(60.0f, sensor.getHumidityData());
 }

 void test_temp_humid_sensor_methods(void) {
    RUN_TEST(test_sensor_initialization);
    RUN_TEST(test_sensor_normal_reading);
    RUN_TEST(test_sensor_error_handling);
    RUN_TEST(test_sensor_averaging);
 }