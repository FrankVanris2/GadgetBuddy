/*
* By: Frank Vanris
* Date: 8/12/2024
* Desc: Creating a manager class that will hold all of the important setups
* and loops for the gadget that I will be making*/
#include "manager/GadgetBuddyManager.h"
#include "LCDDisplay/LCDScreen.h"

//universal object
GadgetBuddyManager gadgetBuddyManager;

GadgetBuddyManager::GadgetBuddyManager() {
    // Constructor can be used to initialize any member variables if needed
}

//setup for all setup functions
void GadgetBuddyManager::setup() {
    lcdScreen.setup();
}


//loop for all loop functions
void GadgetBuddyManager::loop() {

}