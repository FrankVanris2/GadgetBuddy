/**
 * By: Frank Vanris
 * Date: 7/20/2025
 * Desc: Creating a button interface that is meant for the buttons class implementation
 */

 #ifndef BUTTON_INTERFACE_H
 #define BUTTON_INTERFACE_H

 #include "MachineComponentsInterface.h"

class ButtonInterface : public MachineComponentsInterface {

public:
    virtual ~ButtonInterface() = default;

    void setup() override = 0;
    void loop() override = 0;

    // function that focuses on Button debouncing
    virtual void processButtonDebounce(int currentReading, unsigned long currentTime,
                               int& lastRawState, int& debouncedState,
                               unsigned long& lastDebounceTimer,
                               bool isLeftButton) = 0;
};

#endif