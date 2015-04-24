/*
File: protect.cpp

This file implements protections for Arduino_Control.ino 

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
#include "protect.h"


void system_protect(uint8_t state){

  pinMode(PIN_M1_PWM, INPUT);
  pinMode(PIN_M1_IN1, INPUT);
  pinMode(PIN_M1_IN2, INPUT);
  
  pinMode(PIN_M1_PWM, INPUT);
  pinMode(PIN_M1_IN1, INPUT);
  pinMode(PIN_M1_IN2, INPUT);
  
  
  
  // Later replace by EEPROM SAVE. 
  Serial.print("Failure State: ");
  switch(state){
    case NOGROUND:      Serial.println("No ground detected"); break;
    case OVERCURRENT:   Serial.println("Motor Overcurrent"); break;
    case SHORTCIRCUIT:  Serial.println("Motor Diagnostic Problem"); break;
      
  }
}




//void ir_protect(){
//  // pass. Currently we shall employ  no particular protection for IR values.
//}


void m_current_protect(float m1_curr, float m2_curr){
  
  if (m1_curr > MAX_CURRENT || m1_curr > MAX_CURRENT){
    system_protect(OVERCURRENT);
  }
}


//void m_diagnostics_protect(){
//
//  // Check Status on M1_DIAG1
//  digitalWrite(PIN_DM_S0, LOW);
//  digitalWrite(PIN_DM_S0, LOW);
//  if (digitalRead(PIN_DM_Y) == LOW){ system_protect(SHORTCIRCUIT); }
//  
//    // Check Status on M1_DIAG2
//  digitalWrite(PIN_DM_S0, LOW);
//  digitalWrite(PIN_DM_S0, HIGH);
//  if (digitalRead(PIN_DM_Y) == LOW){ system_protect(SHORTCIRCUIT); }
//  
//    // Check Status on M2_DIAG1
//  digitalWrite(PIN_DM_S0, HIGH);
//  digitalWrite(PIN_DM_S0, LOW);
//  if (digitalRead(PIN_DM_Y) == LOW){ system_protect(SHORTCIRCUIT); }
//  
//    // Check Status on M2_DIAG2
//  digitalWrite(PIN_DM_S0, HIGH);
//  digitalWrite(PIN_DM_S0, HIGH);
//  if (digitalRead(PIN_DM_Y) == LOW){ system_protect(SHORTCIRCUIT); }
//  
//}
