/**
 * @file GadgetBuddyManager.cpp
 * @author Frank Vanris
 * @date 8/12/2024
 * @brief Implementation of the GadgetBuddyManager class, coordinating all hardware modules and main logic.
 *
 * This file contains the logic for initializing, managing, and updating all essential components
 * of the GadgetBuddy device, including LED, buttons, LCD screen, sensors, and navigation modules.
 */

#include "manager/GadgetBuddyManager.h"
#include "data&states/PinDeclarationsConstants.h"

GadgetBuddyManager gadgetBuddyManager;

GadgetBuddyManager::GadgetBuddyManager() : 
    mLed(LED_RED_PIN, LED_GREEN_PIN, LED_BLUE_PIN),
    mButtons(GB_LEFT_BUTTON_PIN, GB_RIGHT_BUTTON_PIN, GB_MIN_BUTTON_VAL, GB_MAX_BUTTON_VAL, GB_DEBOUNCE_DELAY), 
    mTempHumidSensor(DHT11_PIN, DHTTYPE, DHT_INTERVAL),
    mRtcClock(),
    mAirQual(MQ135_PIN, MQ_INTERVAL),
    mCompass(),
    mLcdScreen(mLed, mButtons, mTempHumidSensor, mRtcClock, mAirQual, mCompass)
{}

void GadgetBuddyManager::setup() {
    mLed.setup();
    mLcdScreen.setup();
    mButtons.setup();
    mTempHumidSensor.setup();
    mRtcClock.setup();
    mAirQual.setup();  
    // mCompass.setup(); // uncomment when using hardware
}

//loop for all loop functions
void GadgetBuddyManager::loop() {
    mButtons.loop();
    mRtcClock.loop();
    mTempHumidSensor.loop();
    mAirQual.loop();
    mLcdScreen.loop();
    // mCompass.loop(); //uncomment when using hardware
}
