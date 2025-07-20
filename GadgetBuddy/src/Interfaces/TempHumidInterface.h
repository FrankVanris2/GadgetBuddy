/**
 * By: Frank Vanris
 * Date: 7/20/2025
 * Desc: Creating a interface around the DHT11 Sensor
 */

 #pragma once

 #include "MachineComponentsInterface.h"

class TempHumidInterface : public MachineComponentsInterface {
public:  

    virtual ~TempHumidInterface() = default;
    void setup() override = 0;
    void loop() override = 0;

    virtual void obtainingTemperature_HumidityData() = 0;
    virtual float averagingTempData(float temp) = 0;
    virtual float averagingHumidData(float humidity) = 0;
    virtual const char* getErrorMessage() = 0;
};