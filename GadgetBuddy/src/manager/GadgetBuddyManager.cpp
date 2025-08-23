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
    mTempHumidSensor(DHT11_PIN, DHTTYPE, DHT_INTERVAL),
    mRtcClock(),
    // mAirQual(MQ135_PIN, MQ_INTERVAL),
    mCompass(),
    mRadio(),
    mLcdScreen(mButtons, mTempHumidSensor, mRtcClock, mCompass, mRadio)
    
{}

//setup for all setup functions
void GadgetBuddyManager::setup() {

    // 1. Setup radio FIRST on standard I2C
    mRadio.setup();

    // 2. Setup non-I2C components
    mButtons.setup();
    mTempHumidSensor.setup();
    // mAirQual.setup();

    // 3. Setup LCD (redirects Wire to GPIO 25/26)
    mLcdScreen.setup();
    
    // 4. Setup other I2C devices (use existing Wire setup)
    // mCompass.setup(); // uncomment when using hardware
    mRtcClock.setup();
}

//loop for all loop functions
void GadgetBuddyManager::loop() {
    mButtons.loop();
    mTempHumidSensor.loop();
    // mAirQual.loop();
    mLcdScreen.loop();
    // mCompass.loop(); //uncomment when using hardware
    mRtcClock.loop();
}
 