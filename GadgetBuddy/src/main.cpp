/*
* By: Frank Vanris
* Date: 8/12/2024
* Desc: the main where the manager will concurrently allow the gadget to run*/
#include <Arduino.h>
#include "manager/GadgetBuddyManager.h"


//MAIN setup
void setup() {  
  Serial.begin(115200);
  gadgetBuddyManager.setup();
}

//MAIN loop
void loop() {
  gadgetBuddyManager.loop();
}

