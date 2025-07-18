/**
 * By: Frank Vanris 
 * Date: 7/17/2025
 * Desc: My unit tests for the Buttons class that I have currently developed
 */

 #pragma once
 #include <unity.h>
#include "Buttons/Buttons.h"
#include "data&states/PinDeclarationsConstants.h"




void test_button_mechanics(void) {
    Buttons buttons(GB_LEFT_BUTTON_PIN, GB_RIGHT_BUTTON_PIN, GB_MIN_BUTTON_VAL, GB_MAX_BUTTON_VAL, GB_DEBOUNCE_DELAY);

    
}