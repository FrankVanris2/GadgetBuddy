/**
 * By: Frank Vanris
 * Date: 7/17/2025
 * Desc: Creating a file to store essential pins and data
 */

 #ifndef PIN_DECLARATION_CONSTANTS_H
 #define PIN_DECLARATION_CONSTANTS_H

 /** Button essential information */
 #define GB_LEFT_BUTTON_PIN 13
 #define GB_RIGHT_BUTTON_PIN 12
 #define GB_MIN_BUTTON_VAL 0
 #define GB_MAX_BUTTON_VAL 3
 #define GB_DEBOUNCE_DELAY 50

/** DHT11 essential information */
#define DHT11_PIN 11
#define DHT_INTERVAL 5000
#define DHTTYPE DHT11

#endif
