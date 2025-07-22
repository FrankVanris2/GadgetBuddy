/**
 * By: Frank Vanris
 * Date: 7/22/2025
 * Desc: Unit tests for the MockButtons class functionality
 */

#pragma once

#include <unity.h>
#include "MockButtons.h"

// ## Initialization Tests ##

void test_buttons_initialization(void) {
    TEST_MESSAGE("Test: Buttons Initialization");
    MockButtons buttons(13, 12, 0, 3, 50);
    buttons.setup();

    // Should start at minimum value (0)
    TEST_ASSERT_EQUAL(0, buttons.getButtonVal());
}

void test_buttons_custom_initialization(void) {
    TEST_MESSAGE("Test: Buttons with custom min/max values");
    MockButtons buttons(13, 12, 5, 10, 50);
    buttons.setup();

    // Should start at minimum value (5)
    TEST_ASSERT_EQUAL(5, buttons.getButtonVal());
}

// ## Left Button Tests ##

void test_left_button_single_press(void) {
    TEST_MESSAGE("TEST: Single left button press");
    MockButtons buttons(13, 12, 0, 3, 50);
    buttons.setup();

    // Start at value 2
    buttons.simulateRightButtonPress();
    buttons.simulateRightButtonPress();
    TEST_ASSERT_EQUAL(2, buttons.getButtonVal());

    // Press left button (should decrease)
    buttons.simulateLeftButtonPress();
    TEST_ASSERT_EQUAL(1, buttons.getButtonVal());
}

void test_left_button_multiple_presses(void) {
    TEST_MESSAGE("TEST: Multiple left button presses");
    MockButtons buttons(13, 12, 0, 3, 50);
    buttons.setup();

    // Set to max value first
    for(int i = 0; i < 3; i++) {
        buttons.simulateRightButtonPress();
    }
    TEST_ASSERT_EQUAL(3, buttons.getButtonVal());

    // Press left button multiple times
    buttons.simulateLeftButtonPress(); // 3 -> 2
    buttons.simulateLeftButtonPress(); // 2 -> 1
    buttons.simulateLeftButtonPress(); // 1 -> 0

    TEST_ASSERT_EQUAL(0, buttons.getButtonVal());
}

void test_left_button_at_minimum_boundary(void) {
    TEST_MESSAGE("TEST: Left button at minimum boundary");
    MockButtons buttons(13, 12, 0, 3, 50);
    buttons.setup();

    // Already at minimum (0)
    TEST_ASSERT_EQUAL(0, buttons.getButtonVal());

    // Try to press left button
    buttons.simulateLeftButtonPress();
    TEST_ASSERT_EQUAL(0, buttons.getButtonVal());
}

// ## Right Button TESTS ##

void test_right_button_single_press(void) {
    TEST_MESSAGE("TEST: Single right button press");
    MockButtons buttons(13, 12, 0, 3, 50);
    buttons.setup();

    // Start at 0
    TEST_ASSERT_EQUAL(0, buttons.getButtonVal());

    // Press right button
    buttons.simulateRightButtonPress();
    TEST_ASSERT_EQUAL(1, buttons.getButtonVal());  
}

void test_right_button_multiple_presses(void) {
    TEST_MESSAGE("TEST: Multiple right button pressess");
    MockButtons buttons(13, 12, 0, 10, 50);
    buttons.setup();

    // Ensuring we start at 0
    TEST_ASSERT_EQUAL(0, buttons.getButtonVal());

    for(int i = 0; i < 5; i++) {
        buttons.simulateRightButtonPress();
    }
    TEST_ASSERT_EQUAL(5, buttons.getButtonVal());
}

void test_right_button_at_maximum_boundary(void) {
    TEST_MESSAGE("TEST: Right button press at maximum boundary");
    MockButtons buttons(13, 12, 0, 3, 50);
    buttons.setup();

    // Assure you start at 0
    TEST_ASSERT_EQUAL(0, buttons.getButtonVal());

    for(int i = 0; i < 4; i++) {
        buttons.simulateRightButtonPress();
    }

    // Ensure that the button clicks don't go pass the max
    TEST_ASSERT_EQUAL(3, buttons.getButtonVal());
}

// ## Mixed Button Operations ##

void test_mixed_button_presses(void) {
    TEST_MESSAGE("Test: Mixed left and right button presses");
    MockButtons buttons(13, 12, 0, 5, 50);
    buttons.setup();
    
    // Start at 0, go right to 3
    buttons.simulateRightButtonPress(); // 0 -> 1
    buttons.simulateRightButtonPress(); // 1 -> 2
    buttons.simulateRightButtonPress(); // 2 -> 3
    TEST_ASSERT_EQUAL(3, buttons.getButtonVal());
    
    // Go left to 1
    buttons.simulateLeftButtonPress();  // 3 -> 2
    buttons.simulateLeftButtonPress();  // 2 -> 1
    TEST_ASSERT_EQUAL(1, buttons.getButtonVal());
    
    // Go right to 4
    buttons.simulateRightButtonPress(); // 1 -> 2
    buttons.simulateRightButtonPress(); // 2 -> 3
    buttons.simulateRightButtonPress(); // 3 -> 4
    TEST_ASSERT_EQUAL(4, buttons.getButtonVal());
}

// ## Boundary Value Tests ##

void test_custom_boundary_values(void) {
    TEST_MESSAGE("Test: Custom boundary values");
    MockButtons buttons(13, 12, 10, 15, 50);
    buttons.setup();
    
    // Note: Current implementation starts at 0, but with custom min/max
    // this might need adjustment in your MockButtons constructor
    
    // Test that we can't go below minimum
    for(int i = 0; i < 20; i++) {
        buttons.simulateLeftButtonPress();
    }
    TEST_ASSERT_GREATER_OR_EQUAL(10, buttons.getButtonVal());
    
    // Test that we can't go above maximum
    for(int i = 0; i < 20; i++) {
        buttons.simulateRightButtonPress();
    }
    TEST_ASSERT_LESS_OR_EQUAL(15, buttons.getButtonVal());
}

void test_single_value_range(void) {
    TEST_MESSAGE("Test: Single value range (min == max)");
    MockButtons buttons(13, 12, 5, 5, 50);
    buttons.setup();
    
    // With min == max, value should stay constant
    buttons.simulateLeftButtonPress();
    buttons.simulateRightButtonPress();
    buttons.simulateLeftButtonPress();
    
    // Value should remain within the single allowed value
    TEST_ASSERT_GREATER_OR_EQUAL(5, buttons.getButtonVal());
    TEST_ASSERT_LESS_OR_EQUAL(5, buttons.getButtonVal());
}

// ## Configuration Tests ##

void test_button_pin_configuration(void) {
    TEST_MESSAGE("Test: Button pin configuration");
    MockButtons buttons1(13, 12, 0, 3, 50);
    MockButtons buttons2(8, 9, 0, 3, 50);
    
    // Both should initialize properly with different pins
    buttons1.setup();
    buttons2.setup();
    
    // Both should start at the same initial value
    TEST_ASSERT_EQUAL(buttons1.getButtonVal(), buttons2.getButtonVal());
}

// ## Screen Navigation Simulation ##

void test_screen_navigation_sequence(void) {
    TEST_MESSAGE("Test: Simulating screen navigation");
    MockButtons buttons(13, 12, 0, 3, 50); // 4 screens: MAIN(0), TEMP(1), AIR(2), RADIO(3)
    buttons.setup();
    
    // Navigate through all screens
    TEST_ASSERT_EQUAL(0, buttons.getButtonVal()); // MAIN_SCREEN
    
    buttons.simulateRightButtonPress();
    TEST_ASSERT_EQUAL(1, buttons.getButtonVal()); // TEMP_HUMID_SCREEN
    
    buttons.simulateRightButtonPress();
    TEST_ASSERT_EQUAL(2, buttons.getButtonVal()); // AIR_QUALITY_SCREEN
    
    buttons.simulateRightButtonPress();
    TEST_ASSERT_EQUAL(3, buttons.getButtonVal()); // RADIO_SCREEN
    
    // Navigate back
    buttons.simulateLeftButtonPress();
    TEST_ASSERT_EQUAL(2, buttons.getButtonVal()); // Back to AIR_QUALITY_SCREEN
    
    buttons.simulateLeftButtonPress();
    buttons.simulateLeftButtonPress();
    TEST_ASSERT_EQUAL(0, buttons.getButtonVal()); // Back to MAIN_SCREEN
}

// ## Main Test Runner ##

void test_button_methods(void) {
    // Initialization Tests
    RUN_TEST(test_buttons_initialization);
    RUN_TEST(test_buttons_custom_initialization);
    
    // Left Button Tests
    RUN_TEST(test_left_button_single_press);
    RUN_TEST(test_left_button_multiple_presses);
    RUN_TEST(test_left_button_at_minimum_boundary);
    
    // Right Button Tests
    RUN_TEST(test_right_button_single_press);
    RUN_TEST(test_right_button_multiple_presses);
    RUN_TEST(test_right_button_at_maximum_boundary);
    
    // Mixed Operations
    RUN_TEST(test_mixed_button_presses);
    
    // Boundary Tests
    RUN_TEST(test_custom_boundary_values);
    RUN_TEST(test_single_value_range);
    
    // Configuration Tests
    RUN_TEST(test_button_pin_configuration);
    
    // Application-Specific Tests
    RUN_TEST(test_screen_navigation_sequence);
}