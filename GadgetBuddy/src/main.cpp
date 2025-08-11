/*
* By: Frank Vanris
* Date: 8/12/2024
* Desc: the main where the manager will concurrently allow the gadget to run*/
#include <Arduino.h>
#include "manager/GadgetBuddyManager.h"


//MAIN setup
void setup() {
  #ifdef ESP32
    Serial.begin(115200);
    Serial.println(F("GadgetBuddy starting on ESP32..."));
  #else
  Serial.begin(9600);
  Serial.println(F("GadgetBuddy starting on Arduino..."));
  #endif
  
  gadgetBuddyManager.setup();
}

//MAIN loop
void loop() {
  gadgetBuddyManager.loop();
}

