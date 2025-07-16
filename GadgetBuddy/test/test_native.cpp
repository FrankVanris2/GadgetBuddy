#include <unity.h>
#include "simpleMathTest/basicmathtest.h"
#include "circularBufferTest/circularbuffertest.h"


// Functions to test and setup environment if needed.
void setUp(void) {}

void tearDown(void) {}



int runUnityTests(void) {
    UNITY_BEGIN();
    test_basic_math_operations();
    test_circular_buffer_methods();
    return UNITY_END();
}

int main(void) {
    return runUnityTests();
}


