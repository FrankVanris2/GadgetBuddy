/**
 * By: Frank Vanris
 * Date: 7/17/2025
 * Desc: Creating a file to store essential pins and data
 */

#ifndef PIN_DECLARATION_CONSTANTS_H
#define PIN_DECLARATION_CONSTANTS_H

#include "ScreenStates.h"

// Platform-specific pin definitions
#if defined(ESP32)
    // ESP32 pin definitions 
    #define DHT11_PIN 4
    #define MQ135_PIN 36
    #define GB_LEFT_BUTTON_PIN 18
    #define GB_RIGHT_BUTTON_PIN 19
    #define RADIO_MUTE_PIN 23
    // I2C (0) Pins: SDA = 21, SCL = 22
    #define SDA_PIN 21
    #define SCL_PIN 22
    // I2C (1) Pins: SDA = 25, SCL = 26
    #define RADIO_SDA_PIN 25
    #define RADIO_SCL_PIN 26

#elif defined(ARDUINO_UNO) || defined(ARDUINO_AVR_UNO)
    // Arduino Uno pin definitions
    #define DHT11_PIN 2
    #define MQ135_PIN A0
    #define GB_LEFT_BUTTON_PIN 8
    #define GB_RIGHT_BUTTON_PIN 9
    #define RADIO_MUTE_PIN 7
    // I2C Pins: SDA = A4, SCL = A5
    #define SDA_PIN A4
    #define SCL_PIN A5
    // If you want a second I2C bus, you need a software I2C library for Uno
    #define RADIO_SDA_PIN A2 // Example, change as needed
    #define RADIO_SCL_PIN A3 // Example, change as needed

#else
    #error "Unsupported board! Please define pin mappings for your board."
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
