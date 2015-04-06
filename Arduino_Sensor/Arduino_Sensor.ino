/*

ProjectCurio: Sensor Arduino Sketch

Description:
  Interfaces 5 ultrasonic (HCSR04) Sensors and 6 Analog output IR sensors.
  The main loop takes at most 64ms to execute.


This file is part of ProjectCurio.

ProjectCurio is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ProjectCurio is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with ProjectCurio.  If not, see <http://www.gnu.org/licenses/>.

*/





/* ARDUINO2

Description: Interfaces 2 Sharp's proximity sensors and ultrasonic obstacle detectors.
             This program takes care of overcurrent protection and also calculates the distance 
             by averaging number of consecutive readings

*/

#include <SharpIR.h>
#include <avr/wdt.h>
#define ir A0                //Assign pin for Sharp input
#define model 20150          //Specify the model of sensor used


#define MINREAD 10          //Minimum distance read by Sharp
#define CLOSEOBSTACLE    0
boolean sharp_engage;       //Engages Sharp Protection

boolean closeobstable=false; //Gets true if obstacle is closer than MINREAD




SharpIR sharp(ir, 25, 93, model);

// ir: the pin where your sensor is attached
// 25: the number of readings the library will make before calculating a mean distance
// 93: the difference between two consecutive measurements to be taken as valid
// model: an int that determines your sensor:  1080 for GP2Y0A21Y
//                                            20150 for GP2Y0A02Y
//                                            (working distance range according to the datasheets)

/*Program variables*/
float dis;

/*User functions

1. Updating Sharp readings
Parameters: None
  Returns: float
  
*/

float sharp_update(){
   dis=sharp.distance();  // this returns the distance to the obstacle
   return dis;
}

/* Implements an algorithm which decides if system should be put in PROTECTION MODE based on
   Sharp's-Proximity sensor readings.
  [Read more about PROTECTION MODE in Programmer's Guide.]
  
  Parameters: None
  Returns: "true" if PROTECTION MODE is to be activated, "false" otherwise. (data type: boolean)
*/

boolean sharp_protect(){
  if(dis<MINREAD)
  {
    return true;
  }
}

void system_protect(uint8_t label){
  
}
void setup() {
  
  Serial.begin(9600);
  pinMode (ir, INPUT);
  wdt_enable(WDTO_60MS);

}

void loop() {
wdt_reset();

  // IR Proximity Sensing, Protection
  sharp_update();
  if (sharp_engage){
    if (sharp_protect()){
      system_protect(CLOSEOBSTACLE);
    }
  }
}


