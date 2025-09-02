/**
 * @file TempHumidSensor.cpp
 * @author Frank Vanris
 * @date 7/18/2025
 * @brief Implementation of the TempHumidSensor class for GadgetBuddy.
 *
 * This file contains logic for obtaining temperature and humidity data from the DHT sensor,
 * including averaging, error handling, and integration with the main device workflow.
 */

 #include <Arduino.h>
 #include "TempHumidSensor.h"

const char* DHT_READ_ERROR_MSG = "DHT Read Error!";

 TempHumidSensor::TempHumidSensor(int dataPin, int dht_type, unsigned long dhtInterval) :
    DATA_PIN(dataPin),
    DHT_TYPE(dht_type),
    DHT_INTERVAL(dhtInterval),
    dht(DATA_PIN, DHT_TYPE),
    tempAvgBuffer(5),
    humidityAvgBuffer(5),
    mTemperatureData(0.0f),
    mHumidityData(0.0f),
    mHasError(false),
    previousMillis(0)
    
 {}

 void TempHumidSensor::setup() {
    dht.begin();
    obtainingTemperature_HumidityData();
 }

 void TempHumidSensor::loop() {
    if((unsigned long) (millis() - previousMillis) >= DHT_INTERVAL) {
        previousMillis = millis();
        obtainingTemperature_HumidityData();
    }
 }

 void TempHumidSensor::obtainingTemperature_HumidityData() {
   float humidity = dht.readHumidity();
   float temp = dht.readTemperature();
   if(isnan(temp) || isnan(humidity)) {
      mHasError = true;
      Serial.println(DHT_READ_ERROR_MSG);
   } else {
      clearError();
      mTemperatureData = averagingTempData(temp);
      mHumidityData = averagingHumidData(humidity);
   }
 }

 float TempHumidSensor::averagingTempData(float temp) {
   tempAvgBuffer.push_back(temp);
   if(tempAvgBuffer.isEmpty()) {
      return 0.0f;
   }

   return tempAvgBuffer.sum() / tempAvgBuffer.size();
 }

 float TempHumidSensor::averagingHumidData(float humidity) {
   humidityAvgBuffer.push_back(humidity);
   if(humidityAvgBuffer.isEmpty()) {
      return 0.0f;
   }

   return humidityAvgBuffer.sum() / humidityAvgBuffer.size();
 }

 const char* TempHumidSensor::getErrorMessage() {
   if (hasError()) {
        return DHT_READ_ERROR_MSG;
    }
    return nullptr; // Return nullptr if no error
}



