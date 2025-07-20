/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Displaying information on the LCD screen for users.
 */

 #include <LiquidCrystal_I2C.h>
 #include "LCDScreen.h"
  #include  "data&states/ScreenStates.h"

 
 LCDScreen::LCDScreen(Buttons& buttons_ref, TempHumidSensor& temphumid_ref):
      lcd(0x27, 20, 4),
      mCurrentScreenState(MAIN_SCREEN),
      mButtonsRef(buttons_ref),
      mTempHumidRef(temphumid_ref),
      mTempHumidLastUpdateTime(0),
      TEMP_HUMID_UPDATE_INTERAVAL_S(5000)
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

   // Check for sensor error first
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
      mTempHumidLastUpdateTime = millis();
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
   lcd.setCursor(0,0);
   lcd.print("Main Screen");
 }

 void LCDScreen::displayTemp_HumidityScreen() {
   unsigned long currentMillis = millis();

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

   if(currentMillis - mTempHumidLastUpdateTime >= TEMP_HUMID_UPDATE_INTERAVAL_S) {
      mTempHumidLastUpdateTime = currentMillis;
      lcd.setCursor(7,1);
      lcd.print("            ");
      lcd.setCursor(10,2);
      lcd.print("          ");
   }
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