/*
File: proximity.cpp

This file implements functions for interfacing proximity sensors for Arduino_Control.ino 

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
#include "proximity.h"


void ir_update(byte enable, uint16_t* arrVal){

  uint16_t val = 0;
  
  if (enable & (1<<0)){
    digitalWrite(PIN_AM_S2, LOW);
    digitalWrite(PIN_AM_S1, LOW);
    digitalWrite(PIN_AM_S0, LOW);
    
    delayMicroseconds(5);
    arrVal[0] = analogRead(PIN_AM_Y);
  }  
  
  if (enable & (1<<1)){
    digitalWrite(PIN_AM_S2, LOW);
    digitalWrite(PIN_AM_S1, LOW);
    digitalWrite(PIN_AM_S0, HIGH);
    
    delayMicroseconds(5);
    arrVal[1] = analogRead(PIN_AM_Y);
  }  

  if (enable & (1<<2)){
    digitalWrite(PIN_AM_S2, LOW);
    digitalWrite(PIN_AM_S1, HIGH);
    digitalWrite(PIN_AM_S0, LOW);
    
    delayMicroseconds(5);
    arrVal[2] = analogRead(PIN_AM_Y);
  }  

  if (enable & (1<<3)){
    digitalWrite(PIN_AM_S2, LOW);
    digitalWrite(PIN_AM_S1, HIGH);
    digitalWrite(PIN_AM_S0, HIGH);
    
    delayMicroseconds(5);
    arrVal[3] = analogRead(PIN_AM_Y);
  }  

  if (enable & (1<<4)){
    digitalWrite(PIN_AM_S2, HIGH);
    digitalWrite(PIN_AM_S1, LOW);
    digitalWrite(PIN_AM_S0, LOW);
    
    delayMicroseconds(5);
    arrVal[4] = analogRead(PIN_AM_Y);
  }  

  if (enable & (1<<5)){
    digitalWrite(PIN_AM_S2, HIGH);
    digitalWrite(PIN_AM_S1, LOW);
    digitalWrite(PIN_AM_S0, HIGH);
    
    delayMicroseconds(5);
    arrVal[5] = analogRead(PIN_AM_Y);
  }  

  if (enable & (1<<6)){
    digitalWrite(PIN_AM_S2, HIGH);
    digitalWrite(PIN_AM_S1, HIGH);
    digitalWrite(PIN_AM_S0, LOW);
    
    delayMicroseconds(5);
    arrVal[6] = analogRead(PIN_AM_Y);
  }  

  if (enable & (1<<7)){
    digitalWrite(PIN_AM_S2, HIGH);
    digitalWrite(PIN_AM_S1, HIGH);
    digitalWrite(PIN_AM_S0, HIGH);
    
    delayMicroseconds(5);
    arrVal[7] = analogRead(PIN_AM_Y);
  }  
  
}
