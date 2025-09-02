/**
 * @file ScreenStates.h
 * @author Frank Vanris
 * @date 4/5/2025
 * @brief Enumerates the different display screen states for GadgetBuddy.
 *
 * This file defines the possible screen states used for navigation and display,
 * including main, compass, temperature/humidity, air quality, and error screens.
 */

#ifndef SCREEN_STATES_H
#define SCREEN_STATES_H

/**
 * @enum ScreenStates
 * @brief Represents the available display screens in GadgetBuddy.
 */
enum ScreenStates {
    MAIN_SCREEN = 0,      ///< Main screen (default/home)
    COMPASS_SCREEN,       ///< Compass direction screen
    TEMP_HUMID_SCREEN,    ///< Temperature and humidity screen
    AIR_QUALITY_SCREEN,   ///< Air quality sensor screen
    ERROR_SCREEN,         ///< Error display screen
};

#endif