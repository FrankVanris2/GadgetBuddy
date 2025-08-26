/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Displaying information on the LCD screen for users.
*/

#include <LiquidCrystal_I2C.h>
#include "LCDScreen.h"
#include  "data&states/ScreenStates.h"
#include "Displays/MainScreenStrategy.h"
#include "Displays/CompassScreenStrategy.h"
#include "Displays/TempHumidScreenStrategy.h"
#include "Displays/AirQualityScreenStrategy.h"

 
 LCDScreen::LCDScreen(Buttons& buttons_ref, TempHumidSensor& temphumid_ref, RTCClock& rtc_ref, AirQuality& airqual_ref, Compass& compass_ref):
      lcd(0x27, 20, 4),
      mCurrentScreenState(MAIN_SCREEN),
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
   lcd.init();                      // initialize the lcd 
   lcd.backlight();
   updateAndDisplayScreen(); // testing
 }

 void LCDScreen::loop() {
    updateAndDisplayScreen();
 }

 // this is for testing purposes to ensure that the buttons work
 void LCDScreen::updateAndDisplayScreen() {
   unsigned long currentMillis = millis();

   // Check for errors first
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

   // Screen changed - force update
   if(mCurrentScreenState != desiredScreenState) {
      mCurrentScreenState = desiredScreenState;
      lcd.clear();
      mForceUpdate = true;
      mLastUpdate = currentMillis;
   }

   // Throttle updates to reduce flickering
   if (!mForceUpdate && (currentMillis - mLastUpdate < UPDATE_INTERVAL)) {
      return;
   }

   mLastUpdate = currentMillis;
   mForceUpdate = false;

   // Use Strategy pattern to display the current screen
   DisplayStrategy* currentStrategy = getCurrentDisplayStrategy();
   if (currentStrategy != nullptr) {
      currentStrategy->display(lcd);
   }
 }

// NEW DYNAMIC STRATEGY LOADING FUNCTION:
DisplayStrategy* LCDScreen::getCurrentDisplayStrategy() {
   // Only create new strategy if screen changed
   if(mCurrentScreenState != mLastScreenState) {
      // Clean up old strategy
      delete mCurrentStrategy;
      mCurrentStrategy = nullptr;

      // Create new strategy based on current screen
      switch(mCurrentScreenState) {
         case MAIN_SCREEN:
            mCurrentStrategy = new MainScreenStrategy(mRTCRef);
            break;
         case COMPASS_SCREEN:
            mCurrentStrategy = new CompassScreenStrategy(mCompassRef);
            break;
         case TEMP_HUMID_SCREEN:
            mCurrentStrategy = new TempHumidScreenStrategy(mTempHumidRef);
            break;
         case AIR_QUALITY_SCREEN:
            mCurrentStrategy = new AirQualityScreenStrategy(mAirQualRef);
            break;
         default:
            mCurrentStrategy = new MainScreenStrategy(mRTCRef); // Fallback
            break;
      }

      mLastScreenState = mCurrentScreenState;
   }

   return mCurrentStrategy;
}

// Add destructor to clean up
void LCDScreen::cleanupDisplayStrategy() {
   delete mCurrentStrategy;
   mCurrentStrategy = nullptr;
}

// Add to destructor
LCDScreen::~LCDScreen() {
   cleanupDisplayStrategy();
}

const char* LCDScreen::checkForErrors() {

   // Check RTC error first
   if (mRTCRef.hasError()) {
      return mRTCRef.getErrorMessage();
   }

   // Check for compass error
   if(mCompassRef.hasError()) {
      return mCompassRef.getErrorMessage();
   }

   // Check sensor error
   if (mTempHumidRef.hasError()) {
      return mTempHumidRef.getErrorMessage();
   }

   // Check air quality sensor error
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