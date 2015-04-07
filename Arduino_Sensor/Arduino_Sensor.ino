/*

ProjectCurio: Sensor Arduino Sketch

The program interfaces 3 SHARP sensors, 5 Ultrasonic(HC-SR04) Sensors with optional 
1 SHARP and 1 Ultrasonic sensor. If optional sensors are not interfaced, the pins 
might be used as for extension. It also interfaces 4 forward-facing TCRT5000 via
Analog Multiplexer.

[Refer documentation for details on extensions.]


Author: Abhishek N. Kulkarni, Shruti Phadke
Date Created: 06 April 2015
Acknowledgements: Prof. Milind Patwardhan, Prof. Milind Kamble,
  Prof. Mrunal Shidore, Monica Patel, Aditya Joshi.
  
  

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
along with BCUDProject.  If not, see <http://www.gnu.org/licenses/>.

*/


#include "Global.h"
#include "Proximity.h"


byte ultra_enable = 0x00;        // Bits 5-0 represent 6 ultrasonic sensors. If bit is set --> ultrasonic is enabled.
byte sharp_enable = 0x00;        // Bits 3-0 represent 4 SHARP sensors. If bit is set --> SHARP is enabled.
boolean ir_compensate = false;   // Takes 2 values of TCRT with and without LED turned on.

uint16_t IRValues[4];            // Readings of TCRT5000 sensors as 10-bit ADC value
float SharpValues[4];            // Readings of SHARP sensors (in ?? <units>)
float UltraValues[6];            // Readings of Ultrasonics sensors (in cm)

void setup() {
  Serial.begin(9600);
  
}

uint32_t time = 0;
void loop() {
  
  
  //***********************************************************************************************
  // TCRT5000 Proximity Sensing, Protection: 
  // Observed Run Time: ?? 
  // MAX TIME ALLOCATION: ??
  time = micros();
  
  /* Update the values of 4 IR Proximity sensors */
  ir_update(ir_compensate);
  
  /* Raise alarm to master if object is too close */
  ir_protect();
  
  
  time = micros() - time;
  Serial.print("IR Updated in (us):: ");
  Serial.println(time);
  //***********************************************************************************************


  
  //***********************************************************************************************
  // Sharp Proximity Sensing, Protection: 
  // Observed Run Time: ?? 
  // MAX TIME ALLOCATION: ??
  time = micros();
  
  // Shruti: Your code goes here. 
  
  
  time = micros() - time;
  Serial.print("Sharp Updated in (us):: ");
  Serial.println(time);
  //***********************************************************************************************
  
  
  
  //***********************************************************************************************
  // Ultrasonic Proximity Sensing, Protection: 
  // Observed Run Time: ?? 
  // MAX TIME ALLOCATION: ??
  time = micros();
  
  ultrasonic_update(ultra_enable);
  
  time = micros() - time;

  Serial.print("Ultra Updated in (us):: ");
  Serial.println(time);
  //***********************************************************************************************
  
  Serial.println("---------------------");
  delay(1000);
}


