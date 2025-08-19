/**
 * By: Frank Vanris
 * Date: 7/17/2025
 * Desc: Creating a file to store essential pins and data
 */

 #ifndef PIN_DECLARATION_CONSTANTS_H
 #define PIN_DECLARATION_CONSTANTS_H

 #include "ScreenStates.h"


 #ifdef ESP32
    // ESP32 pin definitions 
    #define DHT11_PIN 4
    #define MQ135_PIN 36
    #define GB_LEFT_BUTTON_PIN 18
    #define GB_RIGHT_BUTTON_PIN 19
    #define RADIO_MUTE_PIN 23
    // I2C Pins: SDA = 21, SCL = 22
#else 
    // Arduino Uno pins (keep existing)
    #define DHT11_PIN 11
    #define MQ135_PIN A0
    #define GB_LEFT_BUTTON_PIN 13
    #define GB_RIGHT_BUTTON_PIN 12
    #define RADIO_MUTE_PIN 10

#endif

 /** Button essential information */

 #define GB_MIN_BUTTON_VAL 0
 #define GB_MAX_BUTTON_VAL 4
 #define GB_DEBOUNCE_DELAY 50
 #define RADIO_DEBOUNCE_DELAY 15

/** DHT11 essential information */
#define DHT_INTERVAL 5000
#define DHTTYPE DHT11

/** MQ135 essential information */
#define MQ_INTERVAL 3000

#endif
