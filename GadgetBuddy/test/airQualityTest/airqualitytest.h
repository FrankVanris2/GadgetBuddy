/**
 * By: Frank Vanris
 * Date: 8/26/2025
 * Desc: Creating Unit Tests for the AirQuality sensor
 */

 #pragma once

 #include <unity.h>
 #include "../mocks/MockArduino.h"
 #include "MockAirQuality.h"

 // Test calculateResistance logic
 void test_calculate_resistance() {
    MockAirQuality aq;
    float resistance = aq.calculateResistance(512);
    TEST_ASSERT_TRUE(resistance > 0);
 }

 // Test calculatePPM logic
 void test_calculate_ppm() {
   MockAirQuality aq;
    float ppm = aq.calculatePPM(512);
    TEST_ASSERT_TRUE(ppm >= 1.0f && ppm <= 10000.0f);
 }

 // Test getAirQualityStatus logic
 void test_get_air_quality_status() {
    MockAirQuality aq;
    aq.setCO2(20.0f);
    aq.setError(false);
    aq.setWarmedUp(true);
    TEST_ASSERT_EQUAL_STRING("EXCELLENT", aq.getAirQualityStatus());

    aq.setCO2(35.0f);
    TEST_ASSERT_EQUAL_STRING("GOOD     ", aq.getAirQualityStatus());

    aq.setError(true);
    TEST_ASSERT_EQUAL_STRING("ERROR  ", aq.getAirQualityStatus());

    aq.setError(false);
    aq.setWarmedUp(false);
    TEST_ASSERT_EQUAL_STRING("WARM UP  ", aq.getAirQualityStatus());
}

 // Test validateSensorReading logic
 void test_validate_sensor_reading() {
   MockAirQuality aq;
    TEST_ASSERT_TRUE(aq.validateSensorReading(400.0f));
    TEST_ASSERT_FALSE(aq.validateSensorReading(0.0f));
    TEST_ASSERT_FALSE(aq.validateSensorReading(20000.0f));
 }

 void test_air_quality_methods(void) {
    RUN_TEST(test_calculate_resistance);
    RUN_TEST(test_calculate_ppm);
    RUN_TEST(test_get_air_quality_status);
    RUN_TEST(test_validate_sensor_reading);
 }