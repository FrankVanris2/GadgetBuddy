/**
 * @file MachineComponentsInterface.h
 * @author Frank Vanris
 * @date 7/4/2025
 * @brief Abstract base class for Arduino-style setup and loop methods.
 *
 * This interface defines the required setup and loop methods for all
 * GadgetBuddy machine components, supporting consistent initialization
 * and periodic updates.
 */

#ifndef MACHINE_COMPONENTS_INTERFACE_H
#define MACHINE_COMPONENTS_INTERFACE_H

/**
 * @class MachineComponentsInterface
 * @brief Abstract base class for Arduino-style components.
 */
class MachineComponentsInterface {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~MachineComponentsInterface() = default;
    
    /**
     * @brief Initialize the component hardware.
     */
    virtual void setup() = 0;

    /**
     * @brief Main loop for updating component state.
     */
    virtual void loop() = 0;
};

#endif // MACHINE_COMPONENTS_INTERFACE_H