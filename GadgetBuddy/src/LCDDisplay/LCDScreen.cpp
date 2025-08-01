/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Displaying information on the LCD screen for users.
 */

 #include <LiquidCrystal_I2C.h>
 #include "LCDScreen.h"
  #include  "data&states/ScreenStates.h"

 
 LCDScreen::LCDScreen(Buttons& buttons_ref, TempHumidSensor& temphumid_ref, RTCClock& rtc_ref):
      lcd(0x27, 20, 4),
      mCurrentScreenState(MAIN_SCREEN),
      mButtonsRef(buttons_ref),
      mTempHumidRef(temphumid_ref),
      mRTCRef(rtc_ref)
{}

 void LCDScreen::setup() {
   lcd.init();                      // initialize the lcd 
   lcd.backlight();
   //displayMainScreen();
   updateAndDisplayScreen(); // testing
 }

 void LCDScreen::loop() {
    updateAndDisplayScreen();
 }

 // this is for testing purposes to ensure that the buttons work
 void LCDScreen::updateAndDisplayScreen() {

   // Check for RTC error first
   const char* rtcErrorMsg = mRTCRef.getErrorMessage();
   if(rtcErrorMsg != nullptr) {
      if(mCurrentScreenState != ERROR_SCREEN) {
         lcd.clear();
         mCurrentScreenState = ERROR_SCREEN;
      }
      displayErrorScreen(rtcErrorMsg);
      return;
   }
   // Check for sensor error second
   const char* sensorErrorMsg = mTempHumidRef.getErrorMessage();
   if(sensorErrorMsg != nullptr) {
      if(mCurrentScreenState != ERROR_SCREEN) {
         lcd.clear();
         mCurrentScreenState = ERROR_SCREEN;
      }
      displayErrorScreen(sensorErrorMsg);
      return;
   }
   int desiredScreenState = mButtonsRef.getButtonVal();

   if(mCurrentScreenState != desiredScreenState) {
      mCurrentScreenState = desiredScreenState;
      lcd.clear();
   }

   switch(mCurrentScreenState) {

      case MAIN_SCREEN:
         displayMainScreen();
         break;

      case TEMP_HUMID_SCREEN:
         displayTemp_HumidityScreen();
         break;

      case AIR_QUALITY_SCREEN:
         displayAirQualityScreen();
         break;
      
      case RADIO_SCREEN:
         displayRadioScreen();
         break;  
   }
 }

 void LCDScreen::displayMainScreen() {
   lcd.setCursor(5,0);
   lcd.print("GadgetBuddy");

   // Date
   lcd.setCursor(0,1);
   lcd.print("Date: ");
   lcd.print(mRTCRef.getDate());

   // Time
   lcd.setCursor(0,2);
   lcd.print("Time: ");
   lcd.print(mRTCRef.getTime());
 }

 void LCDScreen::displayTemp_HumidityScreen() {
   lcd.setCursor(0,0);
   lcd.print("Temp/Humid Screen:");
   
   lcd.setCursor(0,1);
   lcd.print("Temp: ");
   lcd.print(mTempHumidRef.getTemperatureData(), 1);
   lcd.print(" C");

   lcd.setCursor(0,2);
   lcd.print("Humidity: ");
   lcd.print(mTempHumidRef.getHumidityData(), 1);
   lcd.print(" %");
 }

 void LCDScreen::displayAirQualityScreen() {
   lcd.setCursor(0,0);
   lcd.print("Air Quality Screen");
 }

 void LCDScreen::displayRadioScreen() {
   lcd.setCursor(0,0);
   lcd.print("Radio Screen");
 }

 void LCDScreen::displayErrorScreen(const char* errorMessage) {
   lcd.setCursor(0,0);
   lcd.print("SENSOR ERROR:");
   lcd.setCursor(0,1);
   lcd.print(errorMessage);
 }