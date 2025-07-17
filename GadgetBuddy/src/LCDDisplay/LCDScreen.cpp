/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Displaying information on the LCD screen for users.
 */

 #include <LiquidCrystal_I2C.h>
 #include "LCDScreen.h"
 #include "Buttons/Buttons.h"

 // Singelton
 LCDScreen lcdScreen;

 LiquidCrystal_I2C lcd(0x27,20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
 
 LCDScreen::LCDScreen(): mScreenChange(0) {}

 void LCDScreen::setup() {
    lcd.init();                      // initialize the lcd 
   
   // FOR TESTING PURPOSES
   // Print a message to the LCD.
   //  lcd.backlight();
   //  lcd.setCursor(1,0);
   //  lcd.print("Hello, world!");
   //  lcd.setCursor(2,1);
   //  lcd.print("Wokwi burr!");
   //  lcd.setCursor(1,2);
   //  lcd.print("IM DEAD!!!!");
   //  lcd.setCursor(2,3);
   //  lcd.print("oh I'm alive");
   lcd.backlight();
   lcd.setCursor(0,0);
   lcd.print("BUTTON COUNT: ");
   lcd.setCursor(0,1);
   lcd.print("0");
    
 }

 void LCDScreen::loop() {
    // This is where the screen states will be for when the user clicks a button to
    // move between different screens.
    testPrintButtonMechanic();
 }

 // this is for testing purposes to ensure that the buttons work
 void LCDScreen::testPrintButtonMechanic() {
   if(mScreenChange != buttons.getButtonVal()) {
      mScreenChange = buttons.getButtonVal();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("BUTTON COUT: ");
      lcd.setCursor(0,1);
      lcd.print(mScreenChange);
   }
 }