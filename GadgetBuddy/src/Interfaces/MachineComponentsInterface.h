/**
 * By: Frank Vanris
 * Date: 7/4/2025
 * Desc: This file is an Abstract class for the Arduino modes(Setup and Loop).
 */

 #ifndef MACHINE_COMPONENTS_INTERFACE_H
 #define MACHINE_COMPONENTS_INTERFACE_H
 
class MachineComponentsInterface {
 public:
    virtual void setup() = 0;
    virtual void loop() = 0;
    virtual ~MachineComponentsInterface() = default;
};

#endif