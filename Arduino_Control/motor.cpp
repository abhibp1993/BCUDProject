/*
File: motor.cpp

This file implements the motor functionality for Arduino_Control.ino

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

#include "Arduino.h"
#include "global.h"
#include "motor.h"


float maxAccel = 0.15;



float PID(float kp, float ki, float kd, uint16_t refSpeed, uint16_t currSpeed, uint16_t* err_integral, uint16_t* err_lastIter){
  
  float output;
  uint16_t err, err_differential; 
  
  err = refSpeed - currSpeed;
  *(err_integral) += err;
  err_differential = err - *(err_lastIter);
  
  output = kp * err + ki * (*(err_integral)) + kd * err_differential;
  output = (float)output / (2 * MAX_SPEED);
  
  *(err_lastIter) = err;  
  return output;
}


void setPWMFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}


void m_setPWM(uint8_t pin_pwm, float duty){
  static float m1_duty = 0;
  static float m2_duty = 0;
  float min_duty;
  
  /* Update the to-be-applied duty cycle for corresponding motor */
  if (pin_pwm == PIN_M1_PWM){ m1_duty = duty; }
  else if(pin_pwm == PIN_M2_PWM){ m2_duty = duty; }
  else{ return; }
  
  
  /* Choose minimum of required frequencies of both motors */
  min_duty = min(abs(m1_duty), abs(m2_duty));
  
//  if (abs(m1_duty) < abs(m2_duty)){ min_duty = m1_duty; }
//  else { min_duty = m2_duty; }
  
  
  /* Set appropriate frequency of PWM */
  if       (min_duty < 0.08) {}
  else if  (min_duty >= 0.08  && min_duty < 0.30)   {setPWMFrequency(pin_pwm, 1024);}
  else if  (min_duty >= 0.30 && min_duty < 0.50)    {setPWMFrequency(pin_pwm, 0256);}  
  else if  (min_duty >= 0.50  && min_duty < 1.00)   {setPWMFrequency(pin_pwm, 0064);}
  else if  (min_duty >= 1.00)   {setPWMFrequency(pin_pwm, 64);}
  
  /* Set PWM duty */
  analogWrite(pin_pwm, duty);
  
}



void m_updateCurrent(float* m1_curr, float* m2_curr){
  *(m1_curr) = (float)(analogRead(PIN_M1_CS)) / M_CURR_SCALE;
  *(m2_curr) = (float)(analogRead(PIN_M2_CS)) / M_CURR_SCALE;
}

void m1_setSpeed(uint16_t refSpeed, uint16_t currSpeed, float kp, float ki, float kd, boolean pid_engage){
  
  static uint16_t err_integral = 0;
  static uint16_t err_lastIter = 0;  
  static float output = 0.2;
  
  float correction = 0;
  
  /* According to status of pid_engage, set the speed */
  if (pid_engage == true){
    /* Compute the correction for 1 step */
    correction = PID(kp, ki, kd, refSpeed, currSpeed, &err_integral, &err_lastIter);
    
    
    /* Apply the correction such that acceleration is inside bounds */
    if       (abs(correction) < maxAccel) { output =  output + correction; }
    else if  (correction > 0)             { output =  output + maxAccel; }
    else if  (correction < 0)             { output =  output - maxAccel; }
    

    /* Apply correction */
    m_setPWM(PIN_M1_PWM, output);
  }
  else{
    m_setPWM(PIN_M1_PWM, (float)refSpeed / MAX_SPEED);    
  }
}

void m2_setSpeed(uint16_t refSpeed, uint16_t currSpeed, float kp, float ki, float kd, boolean pid_engage){

  static uint16_t err_integral = 0;
  static uint16_t err_lastIter = 0;  
  static float output = 0.0;
  
  float correction = 0;
  
  /* According to status of pid_engage, set the speed */
  if (pid_engage == true){
    /* Compute the correction for 1 step */
    correction = PID(kp, ki, kd, refSpeed, currSpeed, &err_integral, &err_lastIter);
    
    
    /* Apply the correction such that acceleration is inside bounds */
    if       (abs(correction) < maxAccel) { output =  output + correction; }
    else if  (correction > 0)             { output =  output + maxAccel; }
    else if  (correction < 0)             { output =  output - maxAccel; }
    

    /* Apply correction */
    m_setPWM(PIN_M2_PWM, output);
  }
  else{
    m_setPWM(PIN_M2_PWM, (float)refSpeed / MAX_SPEED);    
  }
  
}



void setMaxAcceleration(float val){
  if (val > 0 && val <= 1.0)
    maxAccel = val;
}
