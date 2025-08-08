/**
 * By: Frank Vanris
 * Date: 8/7/2025
 * Desc: Creating a Compass Interface for the GadgetBuddy.
*/

#ifndef COMPASS_INTERFACE_H
#define COMPASS_INTERFACE_H

#include "MachineComponentsInterface.h"

class CompassInterface : public MachineComponentsInterface {
public:
    virtual ~CompassInterface() = default;
    void setup() override = 0;
    void loop() override = 0;
};
#endif