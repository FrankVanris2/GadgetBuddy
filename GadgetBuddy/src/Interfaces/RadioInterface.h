/**
 * By: Frank Vanris
 * Date: 8/12/2025
 * Desc: Creating a Radio interface that will only rely specifically for the radio.
*/

#ifndef RADIO_INTERFACE_H
#define RADIO_INTERFACE_H

#include "MachineComponentsInterface.h"
class RadioInterface : public MachineComponentsInterface {
public:
    virtual ~RadioInterface() = default;

    void setup() override = 0;
    void loop() override = 0;

};

#endif