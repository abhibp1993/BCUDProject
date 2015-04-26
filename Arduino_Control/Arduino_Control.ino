/*
File: Arduino_Control.ino

The program interfaces the 2 motors along with speed encoders and
8 TCRT5000 IR-Proximity sensors with Arduino Mini Pro 16MHz/5V.
Refer to Documentation file for more information.

Author: Abhishek N. Kulkarni
Date Created: 06 April 2015
Acknowledgements: Prof. Milind Patwardhan, Prof. Milind Kamble,
  Prof. Mrunal Shidore, Monica Patel, Shruti Phadke, Aditya Joshi.

Pin Configuration: Refer to global.h file.  


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



/* Implementing Configuratin 2: Rx-Tx communication */
#include <ros.h>
#include <curio_pkg/ard1_sensor_input.h>

#include "global.h"
//#include "proximity.h"
#include "motor.h"
#include "protect.h"

#include <FrequencyTimer2.h>
#include <PololuWheelEncoders.h>


// Motors: Speed and Current
PololuWheelEncoders encoders;

float m1_current = 0;        // in Amps
float m2_current = 0;        // in Amps
uint16_t m1_speed = 0;
uint16_t m2_speed = 0;

// Motor: PID
float m1_kp = 0.5;
float m1_ki = 0.0;
float m1_kd = 0.0;
float m2_kp = 0.5;
float m2_ki = 0.0;
float m2_kd = 0.0;
uint16_t m1_refSpeed = 0, m2_refSpeed = 0;    //speed = 0 ==> brakes applied; speed = -ve => disengage
boolean pid_engage = false;


//ROS Messages
ros::NodeHandle  nh;
curio_pkg::ard1_sensor_input sensorInput;
ros::Publisher chatter("Arduino1_input", &sensorInput);



uint32_t counter = 0;
void T2_OVF(void){
  counter++;
}


void setup(){
  Serial.begin(9600);
  
  pinMode(PIN_M1_PWM, OUTPUT);
  pinMode(PIN_M1_IN1, OUTPUT);
  pinMode(PIN_M1_IN2, OUTPUT);
  pinMode(PIN_M1_ENCA, INPUT);
  pinMode(PIN_M1_ENCB, INPUT);

  pinMode(PIN_M2_PWM, OUTPUT);
  pinMode(PIN_M2_IN1, OUTPUT);
  pinMode(PIN_M2_IN2, OUTPUT);
  pinMode(PIN_M2_ENCA, INPUT);
  pinMode(PIN_M2_ENCB, INPUT);  

  
  encoders.init(PIN_M1_ENCA, PIN_M1_ENCB, PIN_M2_ENCA, PIN_M2_ENCB);
  
  //ROS node setup
  nh.initNode();
  nh.advertise(chatter);
}


uint32_t time =0; 
void loop(){  
  
  //***********************************************************************************************
  // Motor Current, Speed Sensing - Intialize, Protection
  // Observed Run Time:  764 us + [20.35ms]
  // MAX TIME ALLOCATION: 25ms
  //time = micros();
  
  /* SENSE: CURRENT FLOWING THROUGH MOTORS 1, 2 */
  m_updateCurrent(&m1_current, &m2_current);
  
  /* SENSE: SPEED OF MOTORS 1, 2 */
  m_updateSpeed(encoders, &m1_speed, &m2_speed);  
   
  
  //***********************************************************************************************
  
  
  
  //***********************************************************************************************
  // Motor control signals: PID, direct-PWM
  // Observed Run Time: [without PID: 92us], [with PID: 332us]
  // MAX TIME ALLOCATION: 500us
  
  //time = micros();
  
  /* ACTION: SET THE SPEED OF MOTORS 1, 2. PID OR DIRECT METHODS */
  if (pid_engage == true){ 
    m1_setSpeed(m1_refSpeed, m1_speed, m1_kp, m1_ki, m1_kd); 
    m2_setSpeed(m2_refSpeed, m2_speed, m2_kp, m2_ki, m2_kd); 
  }
  else{
    m1_setSpeed(m1_refSpeed); 
    m2_setSpeed(m2_refSpeed);
  }
  
  
  //***********************************************************************************************
  // ROS Communication
  sensorInput.m1.m_speed = m1_speed;
  sensorInput.m1.m_current = m1_current;
  sensorInput.m2.m_speed = m2_speed;
  sensorInput.m2.m_current =  m2_current;
  
  chatter.publish(&sensorInput);
  nh.spinOnce();
  delay(70);
}
