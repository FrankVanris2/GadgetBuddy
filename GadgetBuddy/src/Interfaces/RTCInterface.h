/**
 * By: Frank Vanris
 * Date: 7/26/2025
 * Desc: An interface for the RTC (Real-Time Clock) functionality.
 */

 #ifndef RTC_INTERFACE_H
 #define RTC_INTERFACE_H

 #include "MachineComponentsInterface.h"

 class RTCInterface : public MachineComponentsInterface {
 public:
    
    void setup() override = 0;
    void loop() override = 0;
 };
 #endif 