/*
File: motor.h

This file defines the prototypes of motor functions for Arduino_Control.ino 

Author: Abhishek N. Kulkarni
Date Created: 06 April 2015
Acknowledgements: Prof. Milind Patwardhan, Prof. Milind Kamble,
  Prof. Mrunal Shidore, Monica Patel, Shruti Phadke, Aditya Joshi.


This file is part of BCUDProject.

BCUDProject is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

BCUDProject is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with ProjectCurio.  If not, see <http://www.gnu.org/licenses/>.

*/


/*
FORMULA:

1. Speed vs timeOfPulseOnEncoderChannelA
    speed = (60/(24 * 34.1)) / time
          = 0.07331378299120234 / time
          = 73313.783 / time_in_us
*/


#ifndef MOTOR_H_
#define MOTOR_H_

#include <PololuWheelEncoders.h>

#define M_CURR_SCALE        (0.13) * 1024 / 5.0      // scaling factor = V_perAmp / 5 * 1024
#define MAX_SPEED           330
#define MAX_WAIT_TIME       2000
#define SPEED_CONSTANT      366656.8915
#define CONST_TIME2SPEED    73313.783

void setMaxAcceleration(float val);

void m_updateCurrent(float* m1_curr, float* m2_curr);
void m_updateSpeed(PololuWheelEncoders enc, uint16_t* m1_speed, uint16_t* m2_speed);
void m_updateSpeed(uint16_t* m1_speed, uint16_t* m2_speed);

void m1_setSpeed(uint16_t refSpeed);
void m1_setSpeed(uint16_t refSpeed, uint16_t currSpeed, float kp, float ki, float kd);
void m2_setSpeed(uint16_t refSpeed);
void m2_setSpeed(uint16_t refSpeed, uint16_t currSpeed, float kp, float ki, float kd);

#endif
