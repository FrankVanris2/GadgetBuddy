/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Displaying information on the LCD screen for users.
 */

 #include <LiquidCrystal_I2C.h>
 #include "LCDScreen.h"
 #include "Buttons/Buttons.h"

 
 LCDScreen::LCDScreen(Buttons& buttons_ref):
      lcd(0x27, 20, 4),
      mScreenChange(0),
      mButtonsRef(buttons_ref)
{}

 void LCDScreen::setup() {
    lcd.init();                      // initialize the lcd 
   
   lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print("BUTTON COUNT: ");
   lcd.setCursor(0,1);
   lcd.print("0");   
 }

 void LCDScreen::loop() {
    // This is where the screen states will be for when the user clicks a button to
    // move between different screens.

    // FOR TESTING PURPOSES
    testPrintButtonMechanic();
 }

 // this is for testing purposes to ensure that the buttons work
 void LCDScreen::testPrintButtonMechanic() {
   if(mScreenChange != mButtonsRef.getButtonVal()) {
      mScreenChange = mButtonsRef.getButtonVal();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("BUTTON COUNT: ");
      lcd.setCursor(0,1);
      lcd.print(mScreenChange);
   }
 }