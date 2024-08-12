/*
* By: Frank Vanris
* Date: 8/12/2024
* Desc: Creating a manager class that will hold all of the important setups
* and loops for the gadget that I will be making*/
#include "GadgetBuddyManager.h"
#include <LiquidCrystal_I2C.h>

//universal object
GadgetBuddyManager gadgetBuddyManager;

LiquidCrystal_I2C lcd(0x27,20, 4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//setup for all setup functions
void GadgetBuddyManager::setup() {
    lcd.init();                      // initialize the lcd 
    // Print a message to the LCD.
    lcd.backlight();
    lcd.setCursor(3,0);
    lcd.print("Hello, world!");
    lcd.setCursor(2,1);
    lcd.print("Ywrobot Arduino!");
    lcd.setCursor(0,2);
    lcd.print("Arduino LCM IIC 2004");
    lcd.setCursor(2,3);
    lcd.print("Power By Ec-yuan!");

}


//loop for all loop functions
void GadgetBuddyManager::loop() {

}