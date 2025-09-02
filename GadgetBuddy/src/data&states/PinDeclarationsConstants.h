/**
 * @file PinDeclarationsConstants.h
 * @author Frank Vanris
 * @date 7/17/2025
 * @brief Defines essential pin mappings and constants for GadgetBuddy hardware.
 *
 * This file centralizes all hardware pin assignments and key configuration constants
 * for both ESP32 and Arduino Uno platforms, supporting modular and maintainable code.
 */

#ifndef PIN_DECLARATION_CONSTANTS_H
#define PIN_DECLARATION_CONSTANTS_H

#include "ScreenStates.h"

// Platform-specific pin definitions
#ifdef ESP32
    // ESP32 pin assignments
    #define DHT11_PIN 4              ///< GPIO pin for DHT11 temperature/humidity sensor
    #define MQ135_PIN 36             ///< ADC pin for MQ135 air quality sensor
    #define GB_LEFT_BUTTON_PIN 18    ///< GPIO pin for left navigation button
    #define GB_RIGHT_BUTTON_PIN 19   ///< GPIO pin for right navigation button
    // I2C Pins: SDA = 21, SCL = 22
#else
    // Arduino Uno pin assignments
    #define DHT11_PIN 11             ///< Digital pin for DHT11 sensor
    #define MQ135_PIN A0             ///< Analog pin for MQ135 sensor
    #define GB_LEFT_BUTTON_PIN 13    ///< Digital pin for left button
    #define GB_RIGHT_BUTTON_PIN 12   ///< Digital pin for right button

    #define LED_RED_PIN 9            ///< PWM pin for red LED channel
    #define LED_GREEN_PIN 6          ///< PWM pin for green LED channel
    #define LED_BLUE_PIN 5           ///< PWM pin for blue LED channel
#endif

/** Button essential information */
#define GB_MIN_BUTTON_VAL 0          ///< Minimum button value (screen index)
#define GB_MAX_BUTTON_VAL 3          ///< Maximum button value (screen index)
#define GB_DEBOUNCE_DELAY 50         ///< Debounce delay in milliseconds

/** DHT11 essential information */
#define DHT_INTERVAL 5000            ///< Interval between DHT11 readings (ms)
#define DHTTYPE DHT11                ///< DHT sensor type

/** MQ135 essential information */
#define MQ_INTERVAL 3000             ///< Interval between MQ135 readings (ms)

#endif // PIN_DECLARATION_CONSTANTS_H
