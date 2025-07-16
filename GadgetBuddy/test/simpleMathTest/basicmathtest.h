/**
 * By: Frank Vanris
 * Date: 5/30/2025
 * Desc: Doing basic math tests for testing unit testing environment.
 */

 #pragma once
 #include <unity.h>

// Example test cases
void test_addition(void) {
    TEST_ASSERT_EQUAL(5, 2 + 3);
}

void test_subtraction(void) {
    TEST_ASSERT_EQUAL(3, 7 - 4);
}

void test_multiplication(void) {
    TEST_ASSERT_EQUAL(10, 2 * 5);
}

void test_division(void) {
    TEST_ASSERT_EQUAL(2, 10 / 5);
}

void test_basic_math_operations(void) {
    RUN_TEST(test_addition);
    RUN_TEST(test_subtraction);
    RUN_TEST(test_multiplication);
    RUN_TEST(test_division);
}

