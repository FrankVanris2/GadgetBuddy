/**
 * @file CompassInterface.h
 * @author Frank Vanris
 * @date 8/7/2025
 * @brief Interface for compass sensor modules in GadgetBuddy.
 *
 * This abstract class defines the required methods for any compass sensor implementation,
 * supporting modularity and interchangeability within the GadgetBuddy system.
 */

#ifndef COMPASS_INTERFACE_H
#define COMPASS_INTERFACE_H

#include "MachineComponentsInterface.h"

/**
 * @class CompassInterface
 * @brief Abstract interface for compass sensor modules.
 */
class CompassInterface : public MachineComponentsInterface {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~CompassInterface() = default;

    /**
     * @brief Initialize the compass sensor.
     */
    void setup() override = 0;

    /**
     * @brief Main loop for updating compass readings.
     */
    void loop() override = 0;

    /**
     * @brief Get the current heading in degrees.
     * @return Heading value (0-359).
     */
    virtual int getHeading() const = 0;

    /**
     * @brief Get the cardinal direction as a string (e.g., "N", "NE").
     * @return Direction string.
     */
    virtual const char* getDirection() const = 0;

    /**
     * @brief Get the X-axis reading from the compass sensor.
     * @return X-axis value.
     */
    virtual int getX() const = 0;

    /**
     * @brief Get the Y-axis reading from the compass sensor.
     * @return Y-axis value.
     */
    virtual int getY() const = 0;

    /**
     * @brief Get the Z-axis reading from the compass sensor.
     * @return Z-axis value.
     */
    virtual int getZ() const = 0;

};
#endif