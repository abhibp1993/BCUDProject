/*
File: Arduino_Sensor/Global.h

This file defines the pin configuration for Arduino_Sensor.ino 

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
	2. DM: Digital MUX - 74HC4051 (Will be used with digital signals only)
	
	
Connections:
	We utilize ADC functionality of 5 pins
		A] Sharp 1								--> A0
		B] Sharp 2 								--> A1
		C] Sharp 3								--> A2
		D] Sharp 4								--> A6	(optional)
		E] Analog Multiplexer(AM -- Y)			--> A3
		
	We keep Serial Communication pins available --> 0, 1
	
	We keep I2C Communications Pins available	--> A4, A5
	
	Rest all pins are used as digital input-output.
	

Remark:
	The digital Pins as well as the analog pins (except A4, A5)
	can be altered and assigned as per PCB design convenience. 
	
	Secondly, it would be nice if we could switch between I2C
	and Serial Comm, using a 4-DIP switch configuration.

	This Arduino along with BBB provides the extension capability 
	for IO. The pins which are not in use by Arduino all the time
	might be assigned towards this objective.
	
*/


#ifndef GLOBAL_H_
#define GLOBAL_H_

#define SHARP_MODEL      20150

#define PIN_SHARP_1      A0		// Analog Out:: Sharp 1
#define PIN_SHARP_2      A1		// Analog Out:: Sharp 2
#define PIN_SHARP_3      A2		// Analog Out:: Sharp 3
#define PIN_SHARP_4      A6		// Analog Out:: Sharp 4	(optional)    	

#define PIN_AM_S0        12		// Analog Mux: Select 0   	
#define PIN_AM_S1        A3		// Analog Mux: Select 1   	
#define PIN_AM_S2        A4		// Analog Mux: Select 2   	
#define PIN_AM_Y         A7		// Analog Mux: Output

#define PIN_TCRT_LED     13    	// TCRT LED On/Off switch control

#define PIN_DM_S0         8		// Digital Mux: Select 0
#define PIN_DM_S1         9		// Digital Mux: Select 1
#define PIN_DM_S2        10		// Digital Mux: Select 2
#define PIN_DM_Y         11		// Digital Mux: Output


#define PIN_ECHO_US1      2		// Echo Pin of US1
#define PIN_ECHO_US2      3		// Echo Pin of US2
#define PIN_ECHO_US3      4		// Echo Pin of US3
#define PIN_ECHO_US4      5		// Echo Pin of US4
#define PIN_ECHO_US5      6		// Echo Pin of US5
#define PIN_ECHO_US6      7		// Echo Pin of US6


/* Extension Header's Available */
#define PIN_EXT_AN_1     A5
#define PIN_EXT_AN_2     A3
#define PIN_EXT_DIG_1    13
#define PIN_EXT_DIG_2     5


#endif
