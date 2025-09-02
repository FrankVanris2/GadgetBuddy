/**
 * @file LED.h
 * @author Frank Vanris
 * @date 8/31/2025
 * @brief LED control class for GadgetBuddy, providing status indication based on sensor warnings.
 *
 * This class manages an RGB LED, enabling color changes to indicate safe, warning, or danger states
 * for temperature and air quality. It integrates with screen state logic to provide real-time feedback.
 */

#ifndef LED_H
#define LED_H

#include "Interfaces/LEDInterface.h"
#include "data&states/ScreenStates.h"

/**
 * @class LED
 * @brief Controls an RGB LED for status indication in GadgetBuddy.
 */
class LED : public LEDInterface {
public:
    /**
     * @brief Constructor.
     * @param redPin GPIO pin for red LED channel.
     * @param greenPin GPIO pin for green LED channel.
     * @param bluePin GPIO pin for blue LED channel.
     */
    LED(int redPin, int greenPin, int bluePin);

    /**
     * @brief Initialize the LED hardware.
     */
    void setup() override;

    /**
     * @brief Main loop for updating LED state.
     */
    void loop() override;

    /**
     * @brief Turn the LED red.
     */
    void turnRed() override;

    /**
     * @brief Turn the LED green.
     */
    void turnGreen() override;

    /**
     * @brief Turn the LED yellow.
     */
    void turnYellow() override;

    /**
     * @brief Turn the LED blue.
     */
    void turnBlue() override;

    /**
     * @brief Turn the LED off.
     */
    void turnOff() override;

    /**
     * @brief Update the LED color based on the current screen and sensor values.
     * @param state Current screen state.
     * @param temp Current temperature value.
     * @param airQuality Current air quality value.
     * @param led Reference to the LED object.
     */
    void updateLEDForScreen(ScreenStates state, float temp, float airQuality, LED& led);

private:
    int mRedPin;    ///< GPIO pin for red channel
    int mGreenPin;  ///< GPIO pin for green channel
    int mBluePin;   ///< GPIO pin for blue channel
};

#endif // LED_H