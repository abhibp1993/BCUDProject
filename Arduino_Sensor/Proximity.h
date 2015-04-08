#ifndef PROXIMITY_H_
#define PROXIMITY_H_

#include <SharpIR.h>
#include "Global.h"
#include "Arduino.h"


// TCRT5000 Related Functions
void ir_update(boolean compensate);
void ir_protect();

// Ultrasonic Related Functions
void ultrasonic_update(byte ultra_enable);

// SHARP Functions
void sharp_update(byte sharp_enable);




#endif
