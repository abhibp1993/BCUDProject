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

#ifndef MOTOR_H_
#define MOTOR_H_

#define M_CURR_SCALE        (0.13) * 1024 / 5.0      // scaling factor = V_perAmp / 5 * 1024
#define MAX_SPEED           330

void setMaxAcceleration(float val);

void m_updateCurrent(float* m1_curr, float* m2_curr);
void m1_setSpeed(uint16_t refSpeed, uint16_t currSpeed, float kp, float ki, float kd, boolean pid_engage);
void m2_setSpeed(uint16_t refSpeed, uint16_t currSpeed, float kp, float ki, float kd, boolean pid_engage);

#endif
