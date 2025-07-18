/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Displaying information on the LCD screen for users.
 */

 #include <LiquidCrystal_I2C.h>
 #include "LCDScreen.h"
 #include "Buttons/Buttons.h"
  #include  "data&states/ScreenStates.h"

 
 LCDScreen::LCDScreen(Buttons& buttons_ref):
      lcd(0x27, 20, 4),
      mScreenChange(0),
      mButtonsRef(buttons_ref)
{}

 void LCDScreen::setup() {
    lcd.init();                      // initialize the lcd 
   
   lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print("Main Screen");
   
 }

 void LCDScreen::loop() {
    screenStateChanges(mScreenChange);
 }

 // this is for testing purposes to ensure that the buttons work
 void LCDScreen::screenStateChanges(int screenState) {
   if(screenState != mButtonsRef.getButtonVal()) {
      screenState = mButtonsRef.getButtonVal();

      switch(screenState) {

         case MAIN_SCREEN:
            lcd.clear();
            displayMainScreen();
            break;

         case TEMP_HUMID_SCREEN:
            lcd.clear();
            displayTemp_HumidityScreen();
            break;

         case AIR_QUALITY_SCREEN:
            lcd.clear();
            displayAirQualityScreen();
            break;
         
         case RADIO_SCREEN:
            lcd.clear();
            displayRadioScreen();
            break;   
      }

      setScreenState(screenState);
   }
 }

 void LCDScreen::displayMainScreen() {
   lcd.setCursor(0,0);
   lcd.print("Main Screen");
 }

 void LCDScreen::displayTemp_HumidityScreen() {
   lcd.setCursor(0,0);
   lcd.print("Temperature &");
   lcd.setCursor(0,1);
   lcd.print("Humidity");
   lcd.setCursor(0,2);
   lcd.print("Screen");
 }

 void LCDScreen::displayAirQualityScreen() {
   lcd.setCursor(0,0);
   lcd.print("Air Quality Screen");
 }

 void LCDScreen::displayRadioScreen() {
   lcd.setCursor(0,0);
   lcd.print("Radio Screen");
 }