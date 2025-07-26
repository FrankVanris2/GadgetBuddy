/**
 * By: Frank Vanris
 * Date: 7/20/2025
 * Desc: Creating an LCD Display Interface which will allow me to unit test certain components later
 * in the future.
 */

 #ifndef LCD_INTERFACE_H
 #define LCD_INTERFACE_H

 #include "MachineComponentsInterface.h"

class LCDInterface : public MachineComponentsInterface {
public:
    virtual ~LCDInterface() = default;

    void setup() override = 0;
    void loop() override = 0;

};

#endif