/*
File: protect.h

This file defines prototypes for protections for Arduino_Control.ino 

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

#ifndef PROTECT_H_
#define PROTECT_H_


#define MAX_CURRENT         5.0  //Ampere

// Protection predefinitions -- for system_protect(___) function
#define NOGROUND           0
#define OVERCURRENT        1
#define SHORTCIRCUIT       2


void ir_protect();
void m_current_protect(float m1_curr, float m2_curr);
void m_diagnostics_protect();


#endif /* PROTECT_H_ */
