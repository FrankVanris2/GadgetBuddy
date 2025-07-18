/*
* By: Frank Vanris
* Date: 8/12/2024
* Desc: Creating a manager class that will hold all of the important setups
* and loops for the gadget that I will be making*/
#include "manager/GadgetBuddyManager.h"
#include "data&states/PinDeclarationsConstants.h"

//universal object
GadgetBuddyManager gadgetBuddyManager;

GadgetBuddyManager::GadgetBuddyManager() : 
    mButtons(GB_LEFT_BUTTON_PIN, GB_RIGHT_BUTTON_PIN, GB_MIN_BUTTON_VAL, GB_MAX_BUTTON_VAL, GB_DEBOUNCE_DELAY), 
    mLcdScreen(mButtons) 
{ }

//setup for all setup functions
void GadgetBuddyManager::setup() {
    mButtons.setup();
    mLcdScreen.setup();
}

//loop for all loop functions
void GadgetBuddyManager::loop() {
    mButtons.loop();
    mLcdScreen.loop();
}