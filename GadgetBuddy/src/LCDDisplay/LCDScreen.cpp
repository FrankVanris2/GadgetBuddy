/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Displaying information on the LCD screen for users.
*/

#include <LiquidCrystal_I2C.h>
#include "LCDScreen.h"
#include  "data&states/ScreenStates.h"
#include "Displays/MainScreenStrategy.h"
#include "Displays/TempHumidScreenStrategy.h"
#include "Displays/AirQualityScreenStrategy.h"
#include "Displays/RadioScreenStrategy.h"

 
 LCDScreen::LCDScreen(Buttons& buttons_ref, TempHumidSensor& temphumid_ref, RTCClock& rtc_ref, AirQuality& airqual_ref):
      lcd(0x27, 20, 4),
      mCurrentScreenState(MAIN_SCREEN),
      mButtonsRef(buttons_ref),
      mTempHumidRef(temphumid_ref),
      mRTCRef(rtc_ref),
      mAirQualRef(airqual_ref),
      mLastUpdate(0),
      mForceUpdate(true) 
{
   initializeDisplayStrategies();
}

void LCDScreen::initializeDisplayStrategies() {
   mDisplayStrategies[MAIN_SCREEN] = new MainScreenStrategy(mRTCRef);
   mDisplayStrategies[TEMP_HUMID_SCREEN] = new TempHumidScreenStrategy(mTempHumidRef);
   mDisplayStrategies[AIR_QUALITY_SCREEN] = new AirQualityScreenStrategy(mAirQualRef);
   mDisplayStrategies[RADIO_SCREEN] = new RadioScreenStrategy();
}

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

DisplayStrategy* LCDScreen::getCurrentDisplayStrategy() {
   if (mCurrentScreenState >= 0 && mCurrentScreenState < 4) {
      return mDisplayStrategies[mCurrentScreenState];
   }
   return nullptr;
}

const char* LCDScreen::checkForErrors() {
   // Check RTC error first
   if (mRTCRef.hasError()) {
      return mRTCRef.getErrorMessage();
   }

   // Check sensor error
   if (mTempHumidRef.hasError()) {
      return mTempHumidRef.getErrorMessage();
   }

   return nullptr;
}

void LCDScreen::displayErrorScreen(const char* errorMessage) {
   lcd.setCursor(0,0);
   lcd.print("SYSTEM ERROR: ");
   lcd.setCursor(0,1);
   lcd.print(errorMessage);
   lcd.setCursor(0,2);
   lcd.print("Check connections");
}

   

 