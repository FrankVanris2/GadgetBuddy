/**
 * @file Buttons.h
 * @author Frank Vanris
 * @date 7/17/2025
 * @brief Button handling class for changing between different screen states.
 *
 * This class manages the left and right buttons used for screen navigation,
 * including debouncing logic and value tracking.
 */

#ifndef BUTTONS_H
#define BUTTONS_H

#include "Interfaces/ButtonInterface.h"

/**
 * @class Buttons
 * @brief Handles user input from left and right buttons for screen navigation.
 */
class Buttons : public ButtonInterface {
public:
    /**
     * @brief Constructor for Buttons.
     * @param leftPin GPIO pin for the left button.
     * @param rightPin GPIO pin for the right button.
     * @param minVal Minimum allowed button value.
     * @param maxVal Maximum allowed button value.
     * @param debounceDelayMs Debounce delay in milliseconds.
     */
    Buttons(int leftPin, int rightPin, int minVal, int maxVal, unsigned long debounceDelayMs);

    /**
     * @brief Initializes button pins and internal state.
     */
    void setup() override;

    /**
     * @brief Main loop for updating button states and handling debouncing.
     */
    void loop() override;

    /**
     * @brief Get the current button value (screen state index).
     * @return The current button value.
     */
    int getButtonVal() { return mButtonVal; }

private:
    int mButtonVal;                ///< Current button value (screen state index)
    int mL_LastButtonState;        ///< Last raw state of the left button
    int mR_LastButtonState;        ///< Last raw state of the right button
    int mLButtonState;             ///< Debounced state of the left button
    int mRButtonState;             ///< Debounced state of the right button
    unsigned long lLastDebounceTime; ///< Last debounce timestamp for left button
    unsigned long rLastDebounceTime; ///< Last debounce timestamp for right button

    // Configuration parameters
    const int LEFT_BUTTON_PIN;         ///< GPIO pin for left button
    const int RIGHT_BUTTON_PIN;        ///< GPIO pin for right button
    const int MIN_BUTTON_VAL_LIMIT;    ///< Minimum allowed button value
    const int MAX_BUTTON_VAL_LIMIT;    ///< Maximum allowed button value
    const unsigned long DEBOUNCE_DELAY_MS; ///< Debounce delay in milliseconds

    /**
     * @brief Helper function to process button debouncing.
     * @param currentReading Current raw button reading.
     * @param currentTime Current timestamp.
     * @param lastRawState Reference to last raw state variable.
     * @param debouncedState Reference to debounced state variable.
     * @param lastDebounceTimer Reference to last debounce timer variable.
     * @param isLeftButton True if processing the left button, false for right.
     */
    void processButtonDebounce(int currentReading, unsigned long currentTime,
                               int& lastRawState, int& debouncedState,
                               unsigned long& lastDebounceTimer,
                               bool isLeftButton) override;
};

#endif // BUTTONS_H

