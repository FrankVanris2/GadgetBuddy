# Running Unit Tests with PlatformIO

To ensure your unit tests and source code run correctly, follow these steps:

## Configuration

**1. Add the Native Environment for Unit Testing:** In your `platformio.ini` file, include a `[env: native]` section for running Unity tests.:

```ini
[env:native]
platform = native
test_framework = unity
```

**2. Ensure Your Hardware Environment is Configured:** Include  the relevant hardware environment configuration, such as `uno-r4_wifi`, in your platformio.ini` file.

```ini
[env:uno_r4_wifi] 
platform = renesas-ra 
board = uno_r4_wifi 
framework = arduino 
lib_deps = 
    adafruit/Adafruit Motor Shield V2 Library@^1.1.3 
    SPI adafruit/DHT sensor library@^1.4.6 
    adafruit/Adafruit Unified Sensor@^1.1.14 
    bblanchon/ArduinoJson@^7.1.0 
    TFT_eSPI 
    openagriculturefoundation/rosserial_arduino@0.0.0-alpha+sha.1834b766b0 
    throwtheswitch/Unity@^2.6.0
```

## Running the Tests

**1. Run Unit Tests:** To run your unit tests with the native environment, use the following command:

**a: Running things locally:**
if you want to run things locally without the need of the arduino then you can do so by inputting the below command. This form of unit testing is meant for functionalities that don't rely on the arduino board itself.
```sh
pio test -e native
```

**b: Running things through the microcontroller:**
If you want to run things and test things through your microcontroller you can do so by inputting the below command. If there are specific hardware components that you need to unit test you can do so.
```sh
platformio test -e uno
```

**2. Compile and Upload Source Code:** To compile and upload your source code for the specified hardware environment, use: 

**Boards:** uno, uno_r4_wifi, etc.
```sh
pio run -e uno_r4_wifi
```

## Preventing Platform clashes
In order to ensure that both your native and local testing environments are not clashing, be sure to add the conditional macro statement inside of your microcontroller testing environment. This will be most essential when testing both seperately.

```cpp
// cpp uno example test file:
#ifdef ARDUINO // Add this at the beginning
#include <Arduino.h>
#include <unity.h>

// ... Your unit testing code here ...

#endif // Add this ending conditional statement
```

## Uploading your code to Microcontroller
When it comes to uploading code to a specific board, it get's quite annoying to see the native environment fail over and over again since it's meant for unit testing nothing else. That is why it is best to upload the code specifically to the board through this pio command:

**Boards:** uno, uno_r4_wifi, etc.

```sh
platformio run --target upload --environment uno_r4_wifi
```

Following these instructions will help ensure your unit tests and source code are handled in the correct environments.