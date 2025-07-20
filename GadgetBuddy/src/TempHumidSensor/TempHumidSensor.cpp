/**
 * By: Frank Vanris
 * Date: 7/18/2025
 * Desc: Obtaining Temperature Data and Humidity Data from the DHT Sensor
 */

 #include <Arduino.h>
 #include "TempHumidSensor.h"

 // Define your error message as a const char* literal (stored in Flash)
const char* DHT_READ_ERROR_MSG = "DHT Read Error!";
const char* NO_ERROR_MSG = nullptr; // Or an empty string literal "" if you prefer

 TempHumidSensor::TempHumidSensor(int dataPin, int dht_type, unsigned long dht_interval) :
    DATA_PIN(dataPin), 
    DHT_TYPE(dht_type),
    DHT_INTERVAL(dht_interval),
    mHasError(false),
    previousMillis(0),
    tempAvgBuffer(10),
    humidityAvgBuffer(10),
    dht(DATA_PIN, DHT_TYPE)
 {}

 void TempHumidSensor::setup() {
    dht.begin();
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
      mHasError = false;
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
   if (mHasError) {
        return DHT_READ_ERROR_MSG;
    }
    return NO_ERROR_MSG; // Return nullptr if no error
}



