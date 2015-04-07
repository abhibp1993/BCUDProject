#ifndef PROXIMITY_H_
#define PROXIMITY_H_

#include "Global.h"
#include "Arduino.h"

// TCRT5000 Related Functions
void ir_update(boolean compensate);
void ir_protect();

// Ultrasonic Related Functions
void ultrasonic_update(byte ultra_enable);


#endif
