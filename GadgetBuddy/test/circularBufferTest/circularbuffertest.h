/**
 * By: Frank Vanris
 * Date: 7/15/2025
 * Desc: Comprehensive unit tests to ensure that the circular buffer works as intended,
 * covering various states, operations, and edge cases.
 * Compatible with MockCircularBuffer.h without console output.
 */

#pragma once
#include <unity.h>
#include "MockCircularBuffer.h" // Ensure this header contains both declarations and definitions

// --- Helper Functions ---

// Helper to fill a buffer with a sequence of integers
void fillBuffer(MockCircularBuffer<int>& buffer, int count, int start_value = 0) {
    for (int i = 0; i < count; i++) {
        buffer.push_back(start_value + i);
    }
}

// --- Test Cases ---

// ## Initialization and State Tests ##

void test_initial_state_empty_buffer(void) {
    MockCircularBuffer<int> intBuffer(5); // Capacity to hold 5 elements
    TEST_MESSAGE("Test: Initial state of an empty buffer (capacity 5)");
    TEST_ASSERT_TRUE(intBuffer.isEmpty());
    TEST_ASSERT_FALSE(intBuffer.isFull());
    TEST_ASSERT_EQUAL(0, intBuffer.size()); // Corrected: Initially size is 0
    // For int, T() returns 0. Ensure get_front/get_back don't crash and return default.
    TEST_ASSERT_EQUAL(0, intBuffer.get_front());
    TEST_ASSERT_EQUAL(0, intBuffer.get_back());
}

void test_initial_state_zero_capacity_buffer(void) {
    // A buffer with 0 requested capacity will have an internal capacity of 1 (0+1).
    // This means it can hold 0 elements and is immediately considered full.
    MockCircularBuffer<int> intBuffer(0);
    TEST_MESSAGE("Test: Initial state of a buffer with 0 requested capacity");
    TEST_ASSERT_TRUE(intBuffer.isEmpty());
    TEST_ASSERT_TRUE(intBuffer.isFull()); // It's full because (back + 1) % 1 == front (0+1)%1 == 0, front is 0
    TEST_ASSERT_EQUAL(0, intBuffer.size());
    TEST_ASSERT_EQUAL(0, intBuffer.get_front());
    TEST_ASSERT_EQUAL(0, intBuffer.get_back());
}

// ## Push Operations ##

void test_push_back_to_empty_buffer(void) {
    MockCircularBuffer<int> intBuffer(3);
    TEST_MESSAGE("Test: Push one element to an empty buffer");
    intBuffer.push_back(10);
    TEST_ASSERT_FALSE(intBuffer.isEmpty());
    TEST_ASSERT_FALSE(intBuffer.isFull());
    TEST_ASSERT_EQUAL(1, intBuffer.size());
    TEST_ASSERT_EQUAL(10, intBuffer.get_front());
    TEST_ASSERT_EQUAL(10, intBuffer.get_back());
}

void test_push_back_to_partially_fill_buffer(void) {
    MockCircularBuffer<int> intBuffer(5);
    TEST_MESSAGE("Test: Push multiple elements to partially fill buffer");
    fillBuffer(intBuffer, 3); // Add 0, 1, 2
    TEST_ASSERT_FALSE(intBuffer.isEmpty());
    TEST_ASSERT_FALSE(intBuffer.isFull());
    TEST_ASSERT_EQUAL(3, intBuffer.size());
    TEST_ASSERT_EQUAL(0, intBuffer.get_front());
    TEST_ASSERT_EQUAL(2, intBuffer.get_back());
}

void test_push_back_to_fill_buffer_completely(void) {
    MockCircularBuffer<int> intBuffer(4); // Capacity 4
    TEST_MESSAGE("Test: Push elements to fill buffer completely");
    fillBuffer(intBuffer, 4); // Add 0, 1, 2, 3
    TEST_ASSERT_FALSE(intBuffer.isEmpty());
    TEST_ASSERT_TRUE(intBuffer.isFull());
    TEST_ASSERT_EQUAL(4, intBuffer.size());
    TEST_ASSERT_EQUAL(0, intBuffer.get_front());
    TEST_ASSERT_EQUAL(3, intBuffer.get_back());
}

void test_push_back_when_buffer_is_full_overwrites_oldest(void) {
    MockCircularBuffer<int> intBuffer(3); // Capacity 3
    TEST_MESSAGE("Test: Push to a full buffer (expect overwrite)");
    fillBuffer(intBuffer, 3); // Buffer: [0, 1, 2] (front=0, back=3, size=3, full=true)
    TEST_ASSERT_TRUE(intBuffer.isFull());
    TEST_ASSERT_EQUAL(0, intBuffer.get_front()); // Oldest is 0

    intBuffer.push_back(99); // Overwrites 0. Buffer conceptually: [1, 2, 99]
    TEST_ASSERT_TRUE(intBuffer.isFull()); // Still full
    TEST_ASSERT_EQUAL(3, intBuffer.size()); // Size remains 3
    TEST_ASSERT_EQUAL(1, intBuffer.get_front()); // New oldest is 1
    TEST_ASSERT_EQUAL(99, intBuffer.get_back()); // Newest is 99

    intBuffer.push_back(100); // Overwrites 1. Buffer conceptually: [2, 99, 100]
    TEST_ASSERT_TRUE(intBuffer.isFull());
    TEST_ASSERT_EQUAL(3, intBuffer.size());
    TEST_ASSERT_EQUAL(2, intBuffer.get_front());
    TEST_ASSERT_EQUAL(100, intBuffer.get_back());
}

// ## Pop Operations ##

void test_pop_front_from_empty_buffer(void) {
    MockCircularBuffer<int> intBuffer(5);
    TEST_MESSAGE("Test: Pop from an empty buffer (expect no change)");
    intBuffer.pop_front(); // Should do nothing
    TEST_ASSERT_TRUE(intBuffer.isEmpty());
    TEST_ASSERT_EQUAL(0, intBuffer.size());
    TEST_ASSERT_EQUAL(0, intBuffer.get_front());
}

void test_pop_front_single_element(void) {
    MockCircularBuffer<int> intBuffer(5);
    TEST_MESSAGE("Test: Pop the only element from buffer");
    intBuffer.push_back(123); // Buffer: [123]
    TEST_ASSERT_EQUAL(1, intBuffer.size());

    intBuffer.pop_front(); // Buffer: []
    TEST_ASSERT_TRUE(intBuffer.isEmpty());
    TEST_ASSERT_EQUAL(0, intBuffer.size());
    TEST_ASSERT_EQUAL(0, intBuffer.get_front()); // Should return default T()
}

void test_pop_front_multiple_elements(void) {
    MockCircularBuffer<int> intBuffer(5);
    TEST_MESSAGE("Test: Pop multiple elements from a partially filled buffer");
    fillBuffer(intBuffer, 5); // Buffer: [0, 1, 2, 3, 4] (full)

    intBuffer.pop_front(); // Removes 0. Buffer: [1, 2, 3, 4]
    TEST_ASSERT_EQUAL(4, intBuffer.size());
    TEST_ASSERT_EQUAL(1, intBuffer.get_front());
    TEST_ASSERT_EQUAL(4, intBuffer.get_back()); // Back remains the same

    intBuffer.pop_front(); // Removes 1. Buffer: [2, 3, 4]
    TEST_ASSERT_EQUAL(3, intBuffer.size());
    TEST_ASSERT_EQUAL(2, intBuffer.get_front());
    TEST_ASSERT_EQUAL(4, intBuffer.get_back());
}

void test_pop_all_elements(void) {
    MockCircularBuffer<int> intBuffer(3);
    TEST_MESSAGE("Test: Pop all elements until empty");
    fillBuffer(intBuffer, 3); // Buffer: [0, 1, 2]
    TEST_ASSERT_EQUAL(3, intBuffer.size());

    intBuffer.pop_front(); // [1, 2]
    intBuffer.pop_front(); // [2]
    intBuffer.pop_front(); // []

    TEST_ASSERT_TRUE(intBuffer.isEmpty());
    TEST_ASSERT_EQUAL(0, intBuffer.size());
    TEST_ASSERT_EQUAL(0, intBuffer.get_front());
    TEST_ASSERT_EQUAL(0, intBuffer.get_back());
}

// ## Get Element Operations ##

void test_get_front_accuracy(void) {
    MockCircularBuffer<int> intBuffer(5);
    TEST_MESSAGE("Test: get_front accuracy after push and pop");
    intBuffer.push_back(10); // [10]
    TEST_ASSERT_EQUAL(10, intBuffer.get_front());
    intBuffer.push_back(20); // [10, 20]
    TEST_ASSERT_EQUAL(10, intBuffer.get_front());
    intBuffer.pop_front(); // [20]
    TEST_ASSERT_EQUAL(20, intBuffer.get_front());
    intBuffer.push_back(30); // [20, 30]
    TEST_ASSERT_EQUAL(20, intBuffer.get_front());
}

void test_get_back_accuracy(void) {
    MockCircularBuffer<int> intBuffer(5);
    TEST_MESSAGE("Test: get_back accuracy after push and pop");
    intBuffer.push_back(10); // [10]
    TEST_ASSERT_EQUAL(10, intBuffer.get_back());
    intBuffer.push_back(20); // [10, 20]
    TEST_ASSERT_EQUAL(20, intBuffer.get_back());
    intBuffer.pop_front(); // [20]
    TEST_ASSERT_EQUAL(20, intBuffer.get_back());
    intBuffer.push_back(30); // [20, 30]
    TEST_ASSERT_EQUAL(30, intBuffer.get_back());
}

// ## Size and Full/Empty State Tests ##

void test_size_after_mixed_operations(void) {
    MockCircularBuffer<int> intBuffer(4); // Capacity 4
    TEST_MESSAGE("Test: Size calculation after mixed operations");
    TEST_ASSERT_EQUAL(0, intBuffer.size()); // Empty

    intBuffer.push_back(1); // [1]
    TEST_ASSERT_EQUAL(1, intBuffer.size());

    intBuffer.push_back(2); // [1, 2]
    TEST_ASSERT_EQUAL(2, intBuffer.size());

    intBuffer.pop_front(); // [2]
    TEST_ASSERT_EQUAL(1, intBuffer.size());

    intBuffer.push_back(3); // [2, 3]
    intBuffer.push_back(4); // [2, 3, 4]
    TEST_ASSERT_EQUAL(3, intBuffer.size());
    TEST_ASSERT_FALSE(intBuffer.isFull());

    intBuffer.push_back(5); // [2, 3, 4, 5] (full)
    TEST_ASSERT_EQUAL(4, intBuffer.size());
    TEST_ASSERT_TRUE(intBuffer.isFull());

    intBuffer.push_back(6); // Overwrites 2. [3, 4, 5, 6] (full)
    TEST_ASSERT_EQUAL(4, intBuffer.size());
    TEST_ASSERT_TRUE(intBuffer.isFull());
    TEST_ASSERT_EQUAL(3, intBuffer.get_front());
    TEST_ASSERT_EQUAL(6, intBuffer.get_back());
}

void test_is_full_and_is_empty_flags(void) {
    MockCircularBuffer<int> intBuffer(2); // Capacity 2
    TEST_MESSAGE("Test: isFull and isEmpty flags behavior");
    TEST_ASSERT_TRUE(intBuffer.isEmpty());
    TEST_ASSERT_FALSE(intBuffer.isFull());

    intBuffer.push_back(10); // [10]
    TEST_ASSERT_FALSE(intBuffer.isEmpty());
    TEST_ASSERT_FALSE(intBuffer.isFull());

    intBuffer.push_back(20); // [10, 20] (full)
    TEST_ASSERT_FALSE(intBuffer.isEmpty());
    TEST_ASSERT_TRUE(intBuffer.isFull());

    intBuffer.pop_front(); // [20]
    TEST_ASSERT_FALSE(intBuffer.isEmpty());
    TEST_ASSERT_FALSE(intBuffer.isFull());

    intBuffer.pop_front(); // []
    TEST_ASSERT_TRUE(intBuffer.isEmpty());
    TEST_ASSERT_FALSE(intBuffer.isFull());
}

// ## Circular Behavior Tests ##

void test_circular_wrap_around_push(void) {
    MockCircularBuffer<int> intBuffer(3); // Capacity 3
    TEST_MESSAGE("Test: Circular wrap-around during push operations");
    fillBuffer(intBuffer, 3); // [0, 1, 2]
    TEST_ASSERT_TRUE(intBuffer.isFull());
    TEST_ASSERT_EQUAL(0, intBuffer.get_front());
    TEST_ASSERT_EQUAL(2, intBuffer.get_back());

    intBuffer.push_back(30); // Overwrites 0. Conceptual: [1, 2, 30]
    TEST_ASSERT_TRUE(intBuffer.isFull());
    TEST_ASSERT_EQUAL(1, intBuffer.get_front());
    TEST_ASSERT_EQUAL(30, intBuffer.get_back());

    intBuffer.push_back(40); // Overwrites 1. Conceptual: [2, 30, 40]
    TEST_ASSERT_TRUE(intBuffer.isFull());
    TEST_ASSERT_EQUAL(2, intBuffer.get_front());
    TEST_ASSERT_EQUAL(40, intBuffer.get_back());
}

void test_circular_wrap_around_pop(void) {
    MockCircularBuffer<int> intBuffer(3); // Capacity 3
    TEST_MESSAGE("Test: Circular wrap-around during pop operations");
    fillBuffer(intBuffer, 3); // [0, 1, 2]
    intBuffer.push_back(30); // Overwrites 0. [1, 2, 30]
    intBuffer.push_back(40); // Overwrites 1. [2, 30, 40]

    TEST_ASSERT_EQUAL(2, intBuffer.get_front()); // Current front is 2
    intBuffer.pop_front(); // Removes 2. [30, 40]
    TEST_ASSERT_EQUAL(30, intBuffer.get_front());

    intBuffer.pop_front(); // Removes 30. [40]
    TEST_ASSERT_EQUAL(40, intBuffer.get_front());

    intBuffer.pop_front(); // Removes 40. []
    TEST_ASSERT_TRUE(intBuffer.isEmpty());
}

// ## Circular Buffer Summation Tests ##
void test_summation_buffer_operations(void) {
    MockCircularBuffer<int> sumBuffer(5);
    TEST_ASSERT_TRUE(sumBuffer.isEmpty());

    for(int i = 0; i < 5; i++) {
        sumBuffer.push_back(10);
    }
    TEST_ASSERT_TRUE(sumBuffer.isFull());
    TEST_ASSERT_FALSE(sumBuffer.isEmpty());
    TEST_ASSERT_EQUAL(50, sumBuffer.sum());

    sumBuffer.clear();
    for(int i = 0; i < 5; i++) {
        sumBuffer.push_back(1 * i);
    }
    TEST_ASSERT_TRUE(sumBuffer.isFull());
    TEST_ASSERT_EQUAL(5, sumBuffer.size());
    TEST_ASSERT_EQUAL(10, sumBuffer.sum());
}

void test_float_summation_buffer_operations(void) {
    MockCircularBuffer<float> sumFloatBuffer(10);
    TEST_ASSERT_TRUE(sumFloatBuffer.isEmpty());

    for (int i = 0; i < 10; ++i) {
        float value = static_cast<float>(i) * 1.5f;  // Example: 0.0, 1.5, 3.0, ..., 13.5
        sumFloatBuffer.push_back(value);
    }
    TEST_ASSERT_TRUE(sumFloatBuffer.isFull());
    TEST_ASSERT_FALSE(sumFloatBuffer.isEmpty());
    TEST_ASSERT_EQUAL(10, sumFloatBuffer.size());
    TEST_ASSERT_EQUAL(67.5f, sumFloatBuffer.sum());
}

// ## Circular Buffer Clear Data Tests ##
void test_clear_function_operation(void) {
    MockCircularBuffer<int> clearBuffer(20);
    TEST_ASSERT_TRUE(clearBuffer.isEmpty());
    TEST_ASSERT_FALSE(clearBuffer.isFull());
    TEST_ASSERT_EQUAL(0, clearBuffer.size());
    for(int i = 0; i < 20; i++) {
        clearBuffer.push_back(10);
    }
    TEST_ASSERT_TRUE(clearBuffer.isFull());
    TEST_ASSERT_FALSE(clearBuffer.isEmpty());
    TEST_ASSERT_EQUAL(20, clearBuffer.size());
    
    clearBuffer.clear();
    TEST_ASSERT_TRUE(clearBuffer.isEmpty());
    TEST_ASSERT_FALSE(clearBuffer.isFull());
    TEST_ASSERT_EQUAL(0, clearBuffer.size());

    clearBuffer.push_back(2);
    clearBuffer.push_back(3);
    TEST_ASSERT_FALSE(clearBuffer.isEmpty());
    TEST_ASSERT_EQUAL(2, clearBuffer.size());

    clearBuffer.clear();
    TEST_ASSERT_TRUE(clearBuffer.isEmpty());

    for(int i = 0; i < 100; i++) {
        clearBuffer.push_back(1);
    }
    TEST_ASSERT_TRUE(clearBuffer.isFull());
    TEST_ASSERT_EQUAL(20, clearBuffer.size());

    clearBuffer.clear();
    TEST_ASSERT_TRUE(clearBuffer.isEmpty());
    TEST_ASSERT_FALSE(clearBuffer.isFull());
    TEST_ASSERT_EQUAL(0, clearBuffer.size());
}

// ## Template Type Tests ##

void test_char_buffer_operations(void) {
    MockCircularBuffer<char> charBuffer(3); // Capacity 3
    TEST_MESSAGE("Test: Operations with char type buffer");

    TEST_ASSERT_TRUE(charBuffer.isEmpty());
    charBuffer.push_back('A'); // ['A']
    charBuffer.push_back('B'); // ['A', 'B']
    TEST_ASSERT_EQUAL(2, charBuffer.size());
    TEST_ASSERT_EQUAL('A', charBuffer.get_front());
    TEST_ASSERT_EQUAL('B', charBuffer.get_back());

    charBuffer.push_back('C'); // ['A', 'B', 'C'] (full)
    TEST_ASSERT_TRUE(charBuffer.isFull());
    TEST_ASSERT_EQUAL(3, charBuffer.size());
    TEST_ASSERT_EQUAL('A', charBuffer.get_front());
    TEST_ASSERT_EQUAL('C', charBuffer.get_back());

    charBuffer.push_back('D'); // Overwrites 'A'. ['B', 'C', 'D']
    TEST_ASSERT_TRUE(charBuffer.isFull());
    TEST_ASSERT_EQUAL(3, charBuffer.size());
    TEST_ASSERT_EQUAL('B', charBuffer.get_front());
    TEST_ASSERT_EQUAL('D', charBuffer.get_back());

    charBuffer.pop_front(); // Removes 'B'. ['C', 'D']
    TEST_ASSERT_FALSE(charBuffer.isFull());
    TEST_ASSERT_EQUAL(2, charBuffer.size());
    TEST_ASSERT_EQUAL('C', charBuffer.get_front());
    TEST_ASSERT_EQUAL('D', charBuffer.get_back());
}

// ## Main Test Runner ##

void test_circular_buffer_methods(void) {

    // Initialization and State
    RUN_TEST(test_initial_state_empty_buffer);
    RUN_TEST(test_initial_state_zero_capacity_buffer);

    // Push Operations
    RUN_TEST(test_push_back_to_empty_buffer);
    RUN_TEST(test_push_back_to_partially_fill_buffer);
    RUN_TEST(test_push_back_to_fill_buffer_completely);
    RUN_TEST(test_push_back_when_buffer_is_full_overwrites_oldest);

    // Pop Operations
    RUN_TEST(test_pop_front_from_empty_buffer);
    RUN_TEST(test_pop_front_single_element);
    RUN_TEST(test_pop_front_multiple_elements);
    RUN_TEST(test_pop_all_elements);

    // Get Element Operations
    RUN_TEST(test_get_front_accuracy);
    RUN_TEST(test_get_back_accuracy);

    // Size and Full/Empty State Tests
    RUN_TEST(test_size_after_mixed_operations);
    RUN_TEST(test_is_full_and_is_empty_flags);

    // Circular Behavior Tests
    RUN_TEST(test_circular_wrap_around_push);
    RUN_TEST(test_circular_wrap_around_pop);

    // Circular Buffer Summation Tests
    RUN_TEST(test_summation_buffer_operations);
    RUN_TEST(test_float_summation_buffer_operations);

    // ## Circular Buffer Clear Data Tests ##
    RUN_TEST(test_clear_function_operation);

    // Template Type Tests
    RUN_TEST(test_char_buffer_operations);

}




