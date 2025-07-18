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
      mCurrentScreenState(MAIN_SCREEN),
      mButtonsRef(buttons_ref)
{}

 void LCDScreen::setup() {
    lcd.init();                      // initialize the lcd 
   
   lcd.backlight();
   displayMainScreen();
 }

 void LCDScreen::loop() {
    updateAndDisplayScreen();
 }

 // this is for testing purposes to ensure that the buttons work
 void LCDScreen::updateAndDisplayScreen() {
   int desiredScreenState = mButtonsRef.getButtonVal();
   if(mCurrentScreenState != desiredScreenState) {
      mCurrentScreenState = desiredScreenState;
      lcd.clear();

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
         
         default:
            lcd.setCursor(0,0);
            lcd.print("Screen Error");
            break;
      }
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