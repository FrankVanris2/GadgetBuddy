/**
 * By: Frank Vanris
 * Date: 7/5/2025
 * Desc: Displaying information on the LCD screen for users.
 */

 #include <LiquidCrystal_I2C.h>
 #include "LCDScreen.h"

 // Singelton
 LCDScreen lcdScreen;

 LiquidCrystal_I2C lcd(0x27,20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
 
 LCDScreen::LCDScreen() {
    
 }

 void LCDScreen::setup() {
    lcd.init();                      // initialize the lcd 
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(1,0);
    lcd.print("Hello, world!");
    lcd.setCursor(2,1);
    lcd.print("Wokwi burr!");
    
 }

 void LCDScreen::loop() {
    // This is where the screen states will be for when the user clicks a button to
    // move between different screens.
 }