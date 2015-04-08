

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


//---------------------------------------------------------------------------------------------
//Shruti's earlier code

//#include <SharpIR.h>
//#include <avr/wdt.h>

//#define ir0 A0     
//#define ir1 A1
//#define ir2 A2
//#define ir3 A3
//Assign pin for Sharp input
//#define model 20150          //Specify the model of sensor used


//#define MINREAD 10          //Minimum distance read by Sharp
//#define CLOSEOBSTACLE    0
//boolean sharp_engage;       //Engages Sharp Protection

//boolean closeobstable=false; //Gets true if obstacle is closer than MINREAD




//SharpIR sharp(ir, 25, 93, model);

// ir: the pin where your sensor is attached
// 25: the number of readings the library will make before calculating a mean distance
// 93: the difference between two consecutive measurements to be taken as valid
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)

/*Program variables*/
//float dis;

/*User functions

1. Updating Sharp readings
Parameters: None
  Returns: float
  
*/

//float sharp_update(){
//   dis=sharp.distance();  // this returns the distance to the obstacle
//   return dis;
//}

/* Implements an algorithm which decides if system should be put in PROTECTION MODE based on
   Sharp's-Proximity sensor readings.
  [Read more about PROTECTION MODE in Programmer's Guide.]
  
  Parameters: None
  Returns: "true" if PROTECTION MODE is to be activated, "false" otherwise. (data type: boolean)
*/
//boolean sharp_protect(){
//  if(dis<MINREAD)
//  {
//    return true;
//  }
//}

//void system_protect(uint8_t label){
//  
//}


//---------------------------------------------------------------
// Modified by Abhishek on 07 April 2015; 22:20 hours

#include <SharpIR.h>
#include "Global.h"
#include "Proximity.h"


byte ultra_enable = 0x00;        // Bits 5-0 represent 6 ultrasonic sensors. If bit is set --> ultrasonic is enabled.
byte sharp_enable = 0x00;        // Bits 3-0 represent 4 SHARP sensors. If bit is set --> SHARP is enabled.
boolean ir_compensate = false;   // Takes 2 values of TCRT with and without LED turned on.

uint16_t IRValues[4];            // Readings of TCRT5000 sensors as 10-bit ADC value (0-1023)
float SharpValues[4];            // Readings of SHARP sensors (in cm)
float UltraValues[6];            // Readings of Ultrasonics sensors (in cm)

      

void setup() {
  Serial.begin(9600);
  
  pinMode(PIN_AM_S0, OUTPUT);
  pinMode(PIN_AM_S1, OUTPUT);
  pinMode(PIN_AM_S2, OUTPUT);

  pinMode(PIN_DM_S0, OUTPUT);
  pinMode(PIN_DM_S1, OUTPUT);
  pinMode(PIN_DM_S2, OUTPUT);
  
  pinMode(PIN_ECHO_US1, INPUT);
  pinMode(PIN_ECHO_US2, INPUT);
  pinMode(PIN_ECHO_US3, INPUT);
  pinMode(PIN_ECHO_US4, INPUT);
  pinMode(PIN_ECHO_US5, INPUT);  
  
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
  
  /* Update the selected Sharp Sensors*/ 
  sharp_update(sharp_enable);
  
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


  
  
  
  
//  wdt_reset();

  // IR Proximity Sensing, Protection
//  if(sharp_enable.0=1)
//  { SharpValues[0]=sharp_update();}
//  
//  if(sharp_enable.1=1)
//   { SharpValues[1]=sharp_update();}
//   
//  if(sharp_enable.2=1)
//     {SharpValues[2]=sharp_update();}
//     
//  if(sharp_enable.3=1)
//     {SharpValues[3]=sharp_update():}
//   }
//  }
//  sharp_call();
//  if (sharp_engage){
//    if (sharp_protect()){
//      system_protect(CLOSEOBSTACLE);
//    }
//  }

 
