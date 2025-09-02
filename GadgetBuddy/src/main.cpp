/**
 * @file main.cpp
 * @author Frank Vanris
 * @date 8/12/2024
 * @brief Main entry point for GadgetBuddy, running the central manager.
 *
 * This file initializes the GadgetBuddyManager and starts the main application loop,
 * coordinating all hardware modules and device logic.
 */

#include <Arduino.h>
#include "manager/GadgetBuddyManager.h"

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

void loop() {
  gadgetBuddyManager.loop();
}

