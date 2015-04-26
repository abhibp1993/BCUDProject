#ifndef PROXIMITY_H_
#define PROXIMITY_H_

#include "Global.h"
#include "Arduino.h"

// TCRT5000 Related Functions
//void ir_update(boolean compensate);
void ir_update(uint16_t* arrVal);
void ir_protect();

// Ultrasonic Related Functions
float ultrasonic_update();


#endif
