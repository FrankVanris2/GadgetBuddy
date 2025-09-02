/**
 * By: Frank Vanris
 * Date: 8/5/2025
 * Desc: Creating an Air Quality Interface to make things Modular for this project
*/

#ifndef AIR_QUALITY_INTERFACE_H
#define AIR_QUALITY_INTERFACE_H

#include "MachineComponentsInterface.h"
class AirQualityInterface : public MachineComponentsInterface {
public:
    virtual ~AirQualityInterface() = default;
    void setup() override = 0;
    void loop() override = 0;

    // Pure virtual methods for air quality data
    virtual float getAirQualityData() const = 0;
    virtual float getRawADCReading() const  = 0;
    virtual float getR0Value() const = 0;

};
#endif