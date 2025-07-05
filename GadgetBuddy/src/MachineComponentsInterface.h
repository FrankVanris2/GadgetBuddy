/**
 * By: Frank Vanris
 * Date: 7/4/2025
 * Desc: This file is an Abstract class for the Arduino modes(Setup and Loop).
 */

 #pragma once
 
 class MachineComponentsInterface {
public:
    virtual void setup() = 0;
    virtual void loop() = 0;
 };