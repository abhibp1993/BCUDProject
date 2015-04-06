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
along with ProjectCurio.  If not, see <http://www.gnu.org/licenses/>.
*/



/* Implementing Configuratin 2: Rx-Tx communication */


#include "global.h"
#include "proximity.h"
#include "motor.h"
#include "protect.h"

#include <FrequencyTimer2.h>
#include <PololuWheelEncoders.h>



// IR-Proximity: TCRT5000 via Analog Mux
byte ir_enable = 0xFF;
uint16_t ir_value[8];        // check assignment of TCRT <-> index

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


uint32_t counter = 0;
void T2_OVF(void){
  counter++;
}


void setup(){
  Serial.begin(9600);
  
  pinMode(PIN_AM_S0, OUTPUT);
  pinMode(PIN_AM_S1, OUTPUT);
  pinMode(PIN_AM_S2, OUTPUT);
  
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
   
  pinMode(PIN_DM_S0, OUTPUT);
  pinMode(PIN_DM_S1, OUTPUT);
  pinMode(PIN_DM_Y, INPUT);  
  
  
  encoders.init(2,4,8,7);
  
  // Testing configurations
  pid_engage = false;
  m1_kp = 0.5;
  m1_ki = 0.1;
  
  m1_refSpeed = 100;
  m2_refSpeed = 100;
  
  digitalWrite(PIN_M1_IN1, LOW);
  digitalWrite(PIN_M1_IN2, HIGH);
  analogWrite(9, 100);
}


uint32_t time =0; 
void loop(){  
  
  
  //***********************************************************************************************
  // IR Proximity Sensing, Protection: 
  // Observed Run Time: 1028 micros; 
  // MAX TIME ALLOCATION: 2ms
  time = micros();
  
  
  /* SENSE: IR-PROXIMITY RANGE READINGS */
  ir_update(ir_enable, ir_value);  
  
  /* PROTECTIONS */
  //ir_protect();
  
  time = micros() - time;

  Serial.print("IR Updated in (us):: ");
  Serial.println(time);
  //***********************************************************************************************
  
  
  
  //***********************************************************************************************
  // Motor Current, Speed Sensing - Intialize, Protection
  // Observed Run Time:  764 us + [20.35ms]
  // MAX TIME ALLOCATION: 25ms
  time = micros();
  
  /* SENSE: CURRENT FLOWING THROUGH MOTORS 1, 2 */
  m_updateCurrent(&m1_current, &m2_current);
  
  /* SENSE: SPEED OF MOTORS 1, 2 */
  m_updateSpeed(encoders, &m1_speed, &m2_speed);  
  
  /* PROTECTIONS HERE */
  //  m_current_protect(m1_current, m2_current);
  //  m_diagnostics_protect();
  
  time = micros() - time;  
  Serial.print("Motor Current Updated in (us):: ");
  Serial.println(time);
  
  //***********************************************************************************************
  
  
  
  //***********************************************************************************************
  // Motor control signals: PID, direct-PWM
  // Observed Run Time: [without PID: 92us], [with PID: 332us]
  // MAX TIME ALLOCATION: 500us
  
  time = micros();
  
  /* ACTION: SET THE SPEED OF MOTORS 1, 2. PID OR DIRECT METHODS */
  if (pid_engage == true){ 
    Serial.println("PID"); 
    m1_setSpeed(m1_refSpeed, m1_speed, m1_kp, m1_ki, m1_kd); 
    m2_setSpeed(m2_refSpeed, m2_speed, m2_kp, m2_ki, m2_kd); 
  }
  else{ 
    Serial.println("PWM"); 
    m1_setSpeed(m1_refSpeed); 
    m2_setSpeed(m2_refSpeed);
  }
  
  time = micros() - time;  
  Serial.print("Motor Speed Set in (us):: ");
  Serial.println(time);
  
  
  //***********************************************************************************************
  Serial.println("--------------------------");
  delay(1000);
}
