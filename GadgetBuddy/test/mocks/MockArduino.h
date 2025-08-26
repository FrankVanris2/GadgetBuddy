/**
 * By: Frank Vanris
 * Date: 8/26/2025
 * Desc: Creating a mock Arduino class for testing purposes
*/

#pragma once

// Mock analogRead: returns a fixed value for testing
inline int analogRead(int pin) {
    return 512;
}

// Mock millis: returns an incrementing value
inline unsigned long millis() {
    static unsigned long fakeMillis = 0;
    fakeMillis += 100;
    return fakeMillis;
}

// Mock delay: does nothing in native tests
inline void delay(unsigned long ms) {

}

// Mock Serial: minimal stub
struct MockSerial {
    void begin(unsigned long) {}
    void println(const char*) {}
    void print(const char*) {}
    void println(int) {}
    void print(int) {}
};

static MockSerial Serial;
