#include <unity.h>
#include "basicmathtest.h"


// Functions to test and setup environment if needed.
void setUp(void) {}

void tearDown(void) {}



int runUnityTests(void) {
    UNITY_BEGIN();
    test_basic_math_operations();
    return UNITY_END();
}

int main(void) {
    return runUnityTests();
}


