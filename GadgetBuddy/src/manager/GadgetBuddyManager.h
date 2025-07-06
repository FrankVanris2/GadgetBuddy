/*
* By: Frank Vanris
* Date: 8/12/2024
* Desc: Contains all the important methods needed for the gadget to work
*/
#pragma once

#include "Interfaces/MachineComponentsInterface.h"

class GadgetBuddyManager : public MachineComponentsInterface {
public:

    GadgetBuddyManager();

    void setup() override;
    void loop() override;


private:

};

extern GadgetBuddyManager gadgetBuddyManager;