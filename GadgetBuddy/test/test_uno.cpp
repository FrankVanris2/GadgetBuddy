#ifdef ARDUINO
#include <Arduino.h>
#include <unity.h>

void led_built_in_pin_number(void) {
    TEST_ASSERT_EQUAL(13, LED_BUILTIN);
}

void setup() {
    UNITY_BEGIN();
    RUN_TEST(led_built_in_pin_number);
    UNITY_END();
}


void loop() {}

#endif
