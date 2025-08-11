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

    virtual int getHeading() const = 0;
    virtual const char* getDirection() const = 0;
    virtual int getX() const = 0;
    virtual int getY() const = 0;
    virtual int getZ() const = 0;

};
#endif