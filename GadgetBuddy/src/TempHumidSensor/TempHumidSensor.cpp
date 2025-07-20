/**
 * By: Frank Vanris
 * Date: 7/18/2025
 * Desc: Obtaining Temperature Data and Humidity Data from the DHT Sensor
 */

 #include <Arduino.h>
 #include "TempHumidSensor.h"


 TempHumidSensor::TempHumidSensor(int dataPin, int dht_type, unsigned long dht_interval) :
    DATA_PIN(dataPin), 
    DHT_TYPE(dht_type),
    DHT_INTERVAL(dht_interval),
    mErrorMessage(""),
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

        // Do stuff here
    }
 }

 void TempHumidSensor::obtainingTemperature_HumidityData() {
   float h = dht.readHumidity();
   float t = dht.readTemperature();

   if(isnan(h) || isnan(t)) {

   }
 }



