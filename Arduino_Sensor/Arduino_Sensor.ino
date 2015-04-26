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


// Modified by Abhishek on 07 April 2015; 22:20 hours

#include <ros.h>
#include <curio_pkg/ard2_senor_input.h>

#include "Global.h"
#include "Proximity.h"

byte ultra_enable = 0x00;        // Bits 5-0 represent 6 ultrasonic sensors. If bit is set --> ultrasonic is enabled.
boolean ir_compensate = false;   // Takes 2 values of TCRT with and without LED turned on.

uint16_t ir_value[4];            // Readings of TCRT5000 sensors as 10-bit ADC value
float ultra;

//ROS Messages
ros::NodeHandle  nh2;
curio_pkg::ard2_senor_input sensorInput;
ros::Publisher chatter("Arduino2_input", &sensorInput);

void setup() {
  Serial.begin(9600);
  
  pinMode(PIN_ECHO_US1, INPUT);
  pinMode(PIN_TRIG_US1, OUTPUT);  
  
  //ROS node setup
  nh2.initNode();
  nh2.advertise(chatter);
}

uint32_t time = 0;
void loop() { 
  
  //***********************************************************************************************
  // Ultrasonic Proximity Sensing, Protection: 
  // Observed Run Time: ?? 
  // MAX TIME ALLOCATION: ??
  
  ultra = ultrasonic_update();
 
  //***********************************************************************************************
  //TCRT SENSOR UPDATING AND PROTECTION
  
  /*SENSE: IR-PROXIMITY RANGE READINGS */
  ir_update(ir_value);  
    
    
  //PROTECT
  ir_protect();

  //***********************************************************************************************
  // ROS COMMUNICATION
  sensorInput.TCRT.a0 =ir_value[0];
  sensorInput.TCRT.a1 =ir_value[1];
  sensorInput.TCRT.a2 =ir_value[2];
  sensorInput.TCRT.a3 =ir_value[3];
  sensorInput.sonar = ultra;
  
  
  chatter.publish(&sensorInput);
  nh.spinOnce();
  delay(70);
 
}
