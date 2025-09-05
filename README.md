# GadgetBuddy: A Functional Embedded Device Inspired by the PipBoy

Over the past 3 months, I have designed and built GadgetBuddy, a device inspired by the iconic PipBoy from the Fallout franchise. As a long-time fan of Fallout (especially Fallout New Vegas), I wanted to create a practical, real-world version of the PipBoy, focusing on features that would be genuinely useful in a survival scenario. While time constraints limited the scope of the project, I am proud to have delivered a modular, extensible device that demonstrates core embedded systems concepts and best practices.

<div style="text-align: center;">
<img src="https://github.com/user-attachments/assets/fb1897d2-c71e-400b-8209-96cbfc2160ee" alt="Pipboy from Fallout 3" width="500" height="300">
</div>

## What I Learned

This project was a deep dive into Test Driven Development (TDD) and the SOLID principles of software design. Every feature was developed with testing in mind, and each branch included its own set of unit tests to ensure reliability and maintainability. I learned to balance ambition with realism, focusing on delivering a minimum viable product (MVP) within a tight timeline. This experience taught me to prioritize features, manage scope, and make tough decisions about what to include or defer.

I also gained valuable experience in modular design, allowing components to be swapped or upgraded with minimal impact on the overall system. This approach made the codebase more flexible and easier to maintain.

## Features Implemented in GadgetBuddy

**Added:**
1. Temperature/Humidity sensor with LED status indication (green/yellow/red for safe/moderate/unsafe conditions)
2. RTC clock for accurate timekeeping
3. Compass module (GY-271) for directional awareness
4. Air Quality sensor with LED status indication
5. Button interface for screen navigation
6. Four distinct screen states: Main (clock), Compass, Temp/Humidity, Air Quality

**Not Added (due to time/resource constraints):**
1. Radio screen (for listening to FM stations)
2. On/off button for the radio
3. Rotary encoder for radio station selection
4. Dedicated power switch for standalone operation
5. Battery integration for portable use
6. Battery status display on the main screen

## High-Level Design Architecture

The initial architecture remained largely unchanged throughout development, focusing on modularity and clear separation of concerns.
![GadgetBuddyArchitecture](https://github.com/user-attachments/assets/93aa00ef-e8a5-475b-8d41-6e0748dac4e1)

## Low-Level Design Architecture

**Note:** The Compass module (GY-271) is not depicted in the Wokwi diagram due to the simulator’s limited component library. It connects via standard SDA/SCL I2C lines in hardware.  
Additionally, the RGB LED in Wokwi does not function as expected; however, it works correctly on physical hardware. If you are testing this device yourself, please verify LED functionality using actual hardware rather than the Wokwi simulator
<img width="962" height="577" alt="Architecture_GadgetBuddy" src="https://github.com/user-attachments/assets/93bfd43b-6935-4e5a-bcf6-b356912838ce" />

## Screenshots

### Main Screen
![MainScreen](https://github.com/user-attachments/assets/bfaca8c7-df64-43cd-bdf7-3e3e58ebd339)

### Compass Screen
![CompassScreen](https://github.com/user-attachments/assets/5d50ae83-8e20-4d04-987e-632ac725687a)

### Temp/Humidity Screen
![Temp_HumidityScreen](https://github.com/user-attachments/assets/1f489fa3-9543-4c4d-b737-c9cf1205ef7f)

### Air Quality Screen
![Air_QualScreen](https://github.com/user-attachments/assets/e0faea5d-d1ba-402a-9a00-91ab4aeda657)

## Accomplishments

Despite the limited timeframe, I successfully delivered a modular, testable embedded device that meets the core requirements of a survival assistant. Most components are designed to be easily replaceable or upgradable, and features can be added or removed with minimal refactoring. While not every module (such as the LED or Compass) received full unit test coverage, the project demonstrates a strong commitment to code quality and maintainability.

I also documented the development process and created essential guides for future contributors, including unit testing instructions and hardware integration notes.

## Future Developments for Hobbyists/Developers alike
Since this project has been finalized on my side, that doesn't mean that other people can't continue contributing on this repo. If anyone wishes to continue please go ahead, the last thing I was working on was ensuring compatibility between the ESP32 and the Arduino. And I believe I did so properly. However, the only thing I didn't really finalize was the Low-Level sketch for the ESP32. If anyone wants a starting point here are some things that you can work on:

**Easy:**
- Diagram.Json for ESP32 support
- MQ135 fix for ESP32 support
- Resolve any of the bugs that are minor issues on the current codebase.
- Add a voltage reader mechanic for reading battery life of a standalone battery.
- (**For Hardware Hobbyists**) Add a switch to power on and off the device.

**Medium:**
- Add a calibration mode for the MQ135 sensor to ensure that the MQ135 is properly able to read data.
- Try to reduce memory usage more for the Arduino Uno board.
- Construct a Chassy to store and hold all of the electronic components. (Ensure the design is similar to a PipBoy).

**Hard:**
- Add the Final Radio feature on this device. Ensure a new Screen state.
- Implement a rotary encoder to switch between different stations of the Radio.
- Implement a button that switches off the radio on and off in the background.
- Design a PCB Board with all the given hardware components.

With these starting points, developers can explore ways to enhance the embedded device to suit their own needs—and potentially complete it for sharing with friends and colleagues. While I wish I had more time to dedicate to this project, I’m proud of what I was able to accomplish in just three months. I’m excited to continue building and sharing more projects in the future.

## Essential Documents for Developers

- [Unit Testing with PlatformIO](https://github.com/FrankVanris2/GadgetBuddy/blob/main/Documentation/UnitTestingPlatformIO.md)

---

This project represents a significant step in my journey as an embedded systems developer, combining inspiration from gaming with practical engineering and software
