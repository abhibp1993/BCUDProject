/*
File: global.h

This file defines the pin configuration for Arduino_Control.ino 

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



/*
Conventions:
	0. All definitions with PIN_*** are physical pin connections. Rest are software 
		pre-processor definitions.
	1. AM: Analog MUX  - 74HC4051
	2. DM: Digital MUX - 74151
	
	
Connections:
	We utilize ADC functionality of 3 pins
		A] Motor1_CurrSense; 					-->	A0
		B] Motor2_CurrSense; 					--> A1
		C] Analog Multiplexer's output (Y)		--> A2
	
	We utilize PWM functionality of 2 pins
		A] Motor1_PWM							-->  9
		B] Motor2_PWM							--> 10
	
	We keep Serial Communication pins available --> 0, 1
	
	We keep I2C Communications Pins available	--> A4, A5
	
	Rest all pins are used as digital input-output.
	

Remark:
	The digital Pins as well as the analog pins(except A4, A5)
	can be altered as per PCB design convenience. 
	
	Secondly, it would be nice if we could switch between I2C
	and Serial Comm, using a 4-DIP switch configuration.

*/


#ifndef GLOBAL_H_
#define GLOBAL_H_


#define PIN_AM_S0   		A5		// Analog Mux: Select 0   	
#define PIN_AM_S1   		A3		// Analog Mux: Select 1
#define PIN_AM_S2   		A4 		// Analog Mux: Select 2
#define PIN_AM_Y    		A2		// Analog Mux: Output

#define PIN_M1_CS           A0		// Current Sense
#define PIN_M1_IN1          11  	// Direction Control pin 1
#define PIN_M1_IN2          12  	// Direction Control pin 2
#define PIN_M1_PWM          9		// Speed control pin (0-5V; 31Hz to 500Hz)
#define PIN_M1_ENCA         2		// Encoder Channel A: High frequency signal
#define PIN_M1_ENCB         4   	// Encoder Channel B: High frequency signal

#define PIN_M2_CS           A1		// Current Sense
#define PIN_M2_IN1          6		// Direction Control pin 1
#define PIN_M2_IN2          5		// Direction Control pin 2
#define PIN_M2_PWM          10		// Speed control pin (0-5V; 31Hz to 500Hz)
#define PIN_M2_ENCA         8  		// Encoder Channel A: High frequency signal
#define PIN_M2_ENCB         7  		// Encoder Channel B: High frequency signal

#define PIN_DM_S0           A6 		// Digital Mux: Select 0
#define PIN_DM_S1           A7 		// Digital Mux: Select 1	
#define PIN_DM_Y            3		// Digital Mux: Output	
									// Digital Mux: Select 2 (is GND hard-wired)


#endif 
