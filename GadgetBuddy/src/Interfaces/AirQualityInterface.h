/**
 * @file AirQualityInterface.h
 * @author Frank Vanris
 * @date 8/5/2025
 * @brief Interface for air quality sensor modules in GadgetBuddy.
 *
 * This abstract class defines the required methods for any air quality sensor implementation,
 * supporting modularity and interchangeability within the GadgetBuddy system.
 */

#ifndef AIR_QUALITY_INTERFACE_H
#define AIR_QUALITY_INTERFACE_H

#include "MachineComponentsInterface.h"

/**
 * @class AirQualityInterface
 * @brief Abstract interface for air quality sensor modules.
 */
class AirQualityInterface : public MachineComponentsInterface {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~AirQualityInterface() = default;

    /**
     * @brief Initialize the air quality sensor.
     */
    void setup() override = 0;

    /**
     * @brief Main loop for updating sensor readings.
     */
    void loop() override = 0;

    /**
     * @brief Get the latest air quality data (e.g., CO2 PPM).
     * @return Air quality value.
     */
    virtual float getAirQualityData() const = 0;

    /**
     * @brief Get the latest raw ADC reading from the sensor.
     * @return Raw ADC value.
     */
    virtual float getRawADCReading() const = 0;

    /**
     * @brief Get the sensor's baseline resistance (R0).
     * @return R0 value.
     */
    virtual float getR0Value() const = 0;

};
#endif