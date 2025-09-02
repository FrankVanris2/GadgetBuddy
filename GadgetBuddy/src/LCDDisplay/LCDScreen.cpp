/**
 * @file LCDScreen.cpp
 * @author Frank Vanris
 * @date 7/5/2025
 * @brief Implementation of the LCDScreen class for GadgetBuddy.
 *
 * This file contains the logic for visualizing sensor data and device status
 * on the LCD display, including dynamic screen switching, error handling,
 * and integration with all major hardware modules.
 */

#include <LiquidCrystal_I2C.h>
#include "LCDScreen.h"
#include  "data&states/ScreenStates.h"
#include "Displays/MainScreenStrategy.h"
#include "Displays/CompassScreenStrategy.h"
#include "Displays/TempHumidScreenStrategy.h"
#include "Displays/AirQualityScreenStrategy.h"


LCDScreen::LCDScreen(LED& led_ref, Buttons& buttons_ref, TempHumidSensor& temphumid_ref, RTCClock& rtc_ref, AirQuality& airqual_ref, Compass& compass_ref):
      lcd(0x27, 20, 4),
      mCurrentScreenState(MAIN_SCREEN),
      mLedRef(led_ref),
      mButtonsRef(buttons_ref),
      mTempHumidRef(temphumid_ref),
      mRTCRef(rtc_ref),
      mAirQualRef(airqual_ref),
      mCompassRef(compass_ref),
      mCurrentStrategy(nullptr),
      mLastScreenState(-1), 
      mLastUpdate(0),
      mForceUpdate(true) 
{}

 void LCDScreen::setup() {
   lcd.init();                      
   lcd.backlight();
   updateAndDisplayScreen(); 
 }

 void LCDScreen::loop() {
    updateAndDisplayScreen();
 }

 void LCDScreen::updateAndDisplayScreen() {
   unsigned long currentMillis = millis();

   const char* errorMsg = checkForErrors();
   if(errorMsg != nullptr) {
      if(mCurrentScreenState != ERROR_SCREEN) {
         lcd.clear();
         mCurrentScreenState = ERROR_SCREEN;
         mForceUpdate = true;
      }
      displayErrorScreen(errorMsg);
      return;
   }

   int desiredScreenState = mButtonsRef.getButtonVal();

   if(mCurrentScreenState != desiredScreenState) {
      mCurrentScreenState = desiredScreenState;
      lcd.clear();
      mForceUpdate = true;
      mLastUpdate = currentMillis;
   }

   if (!mForceUpdate && (currentMillis - mLastUpdate < UPDATE_INTERVAL)) {
      return;
   }

   mLastUpdate = currentMillis;
   mForceUpdate = false;

   DisplayStrategy* currentStrategy = getCurrentDisplayStrategy();
   if (currentStrategy != nullptr) {
      currentStrategy->display(lcd);
   }
 }

DisplayStrategy* LCDScreen::getCurrentDisplayStrategy() {
   if(mCurrentScreenState != mLastScreenState) {
      delete mCurrentStrategy;
      mCurrentStrategy = nullptr;

      switch(mCurrentScreenState) {
         case MAIN_SCREEN:
            mCurrentStrategy = new MainScreenStrategy(mRTCRef);
            mLedRef.turnOff();
            break;
         case COMPASS_SCREEN:
            mCurrentStrategy = new CompassScreenStrategy(mCompassRef);
            mLedRef.turnOff();
            break;
         case TEMP_HUMID_SCREEN:
            mCurrentStrategy = new TempHumidScreenStrategy(mTempHumidRef);
            mLedRef.updateLEDForScreen(ScreenStates::TEMP_HUMID_SCREEN, mTempHumidRef.getTemperatureData(), 0.0f, mLedRef);
            break;
         case AIR_QUALITY_SCREEN:
            mCurrentStrategy = new AirQualityScreenStrategy(mAirQualRef);
            mLedRef.updateLEDForScreen(ScreenStates::AIR_QUALITY_SCREEN, 0.0f, mAirQualRef.getAirQualityData(), mLedRef);
            break;
         default:
            mCurrentStrategy = new MainScreenStrategy(mRTCRef); // Fallback
            break;
      }
      mLastScreenState = mCurrentScreenState;
   }
   return mCurrentStrategy;
}

void LCDScreen::cleanupDisplayStrategy() {
   delete mCurrentStrategy;
   mCurrentStrategy = nullptr;
}

LCDScreen::~LCDScreen() {
   cleanupDisplayStrategy();
}

const char* LCDScreen::checkForErrors() {

   if (mRTCRef.hasError()) {
      return mRTCRef.getErrorMessage();
   }

   if(mCompassRef.hasError()) {
      return mCompassRef.getErrorMessage();
   }

   if (mTempHumidRef.hasError()) {
      return mTempHumidRef.getErrorMessage();
   }

   if (mAirQualRef.hasError()) {
      return mAirQualRef.getErrorMessage();
   }

   return nullptr;
}

void LCDScreen::displayErrorScreen(const char* errorMessage) {
   lcd.setCursor(0,0);
   lcd.print(F("SYSTEM ERROR: "));
   lcd.setCursor(0,1);
   lcd.print(errorMessage);
   lcd.setCursor(0,2);
   lcd.print(F("Check connections"));
}