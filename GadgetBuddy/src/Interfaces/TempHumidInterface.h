/**
 * @file TempHumidInterface.h
 * @author Frank Vanris
 * @date 7/20/2025
 * @brief Interface for temperature and humidity sensor modules (e.g., DHT11) in GadgetBuddy.
 *
 * This abstract class defines the required methods for temperature and humidity sensor implementations,
 * supporting modularity and enabling reliable data acquisition and processing.
 */

#ifndef TEMP_HUMID_INTERFACE_H
#define TEMP_HUMID_INTERFACE_H

#include "MachineComponentsInterface.h"

/**
 * @class TempHumidInterface
 * @brief Abstract interface for temperature and humidity sensor modules.
 */
class TempHumidInterface : public MachineComponentsInterface {
public:  
    /**
     * @brief Virtual destructor.
     */
    virtual ~TempHumidInterface() = default;

    /**
     * @brief Initialize the temperature and humidity sensor hardware.
     */
    void setup() override = 0;

    /**
     * @brief Main loop for updating sensor readings.
     */
    void loop() override = 0;

    /**
     * @brief Obtain the latest temperature and humidity data from the sensor.
     */
    virtual void obtainingTemperature_HumidityData() = 0;

    /**
     * @brief Calculate the average temperature from provided data.
     * @param temp The temperature value to include in the average.
     * @return Averaged temperature value.
     */
    virtual float averagingTempData(float temp) = 0;

    /**
     * @brief Calculate the average humidity from provided data.
     * @param humidity The humidity value to include in the average.
     * @return Averaged humidity value.
     */
    virtual float averagingHumidData(float humidity) = 0;
};

#endif