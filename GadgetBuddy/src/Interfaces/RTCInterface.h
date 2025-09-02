/**
 * @file RTCInterface.h
 * @author Frank Vanris
 * @date 7/26/2025
 * @brief Interface for RTC (Real-Time Clock) functionality in GadgetBuddy.
 *
 * This abstract class defines the required methods for RTC implementations,
 * supporting modularity and enabling timekeeping features.
 */

#ifndef RTC_INTERFACE_H
#define RTC_INTERFACE_H

#include "MachineComponentsInterface.h"

/**
 * @class RTCInterface
 * @brief Abstract interface for RTC modules.
 */
class RTCInterface : public MachineComponentsInterface {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~RTCInterface() = default;

    /**
     * @brief Initialize the RTC hardware.
     */
    void setup() override = 0;

    /**
     * @brief Main loop for updating RTC state.
     */
    void loop() override = 0;
};

#endif // RTC_INTERFACE_H