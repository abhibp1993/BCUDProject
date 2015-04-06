/*

ProjectCurio: Control Arduino Sketch

Description:
  Interfaces two motors along with respective quadrature encoders. Further, the program
  gathers information on current through motors and their failure states of the motor. 
  Also, 4 IR proximity sensors sense the ground existence to provide protection against
  falling off from tall surface.
  

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


// Protection predefinitions -- for system_protect(___) function
#define NOGROUND           0
#define OVERCURRENT        1
#define SHORTCIRCUIT       2

// Pin Configuration

//#define PIN_IR_0           A0
//#define PIN_IR_1           A1
//#define PIN_IR_2           A2
//#define PIN_IR_3           A3

#define PIN_M1_CS          A0
#define PIN_M1_IN1         A4
#define PIN_M1_IN2         A5
#define PIN_M1_PWM         9
//#define PIN_M1_DIAG1       00
//#define PIN_M1_DIAG2       00
#define PIN_M1_ENCA        7
#define PIN_M1_ENCB        8


#define PIN_M2_CS          A1
#define PIN_M2_IN1         2
#define PIN_M2_IN2         3
#define PIN_M2_PWM         10
//#define PIN_M2_DIAG1       00
//#define PIN_M2_DIAG2       00
#define PIN_M2_ENCA        5
#define PIN_M2_ENCB        6


#define BRAKING_DELAY      250    //in us

#include <avr/wdt.h>


// Motor 1: Configuration Variables
float      m1_Kp = 0.1;
float      m1_Ki = 0.0;
float      m1_Kd = 0.0;
float      m1_pwm = 0;
boolean    m1_isClockwise = true;
boolean    m1_tobeReversed = false;
uint16_t   m1_current = 0;
uint32_t   m1_encoder = 0;
uint16_t   m1_speed = 0;
uint16_t   m1_refSpeed = 0;

// Motor 2: Configuration Variables
float      m2_Kp = 0.1;
float      m2_Ki = 0.0;	
float      m2_Kd = 0.0;
float      m2_pwm = 0;
boolean    m2_isClockwise = true;
boolean    m2_tobeReversed = false;
uint16_t   m2_current = 0;
uint32_t   m2_encoder = 0;
uint16_t   m2_speed = 0;
uint16_t   m2_refSpeed = 0;


// IR Proximity Readings
boolean ir_engage;    // engages IR protection
uint16_t   ir[4];

// General Configuration
boolean   PID_Engage = true;


// Fail States
boolean   m_failure = false;  // true if any overload/short-circuit/over-heating failure is signalled by driver






// ==============================================================================================================
// Helper Functions: General


/*
  Sets the frequency of PWM for pins 3, 5, 6, 9, 10, 11 (PWM Pins of Arduino)
  
  Parameters:
    1. pin: pin number from {3, 5, 6, 9, 10, 11}
    2. divisor: is the prescalar value from {1, 8, 64, 256, 1024}, {32} -- if pin is 3 or 11.
    
  Returns: None
  
  Description:
    The routine operates by updating the prescalar value of ATMEGA 328/168 timers.
    The pins are connected as shown below 
              5, 6  -- T0
              9, 10 -- T1
              3, 11 -- T2
    The timers are used internally by Arduino inbuilt libraries for delay routines etc. 
    Calling this routine may disrupt the following functions.
    
    Changes on 3, 5, 6, 11:: delay(), millis() function can go to hell!
    Changes on 9, 10      :: Servo functionality.. puff!!! gone!
    
    Credits: http://playground.arduino.cc/Code/PwmFrequency
*/
void setPWMFrequency(int pin, int divisor) {
  byte mode;
  if(pin == 5 || pin == 6 || pin == 9 || pin == 10) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 64: mode = 0x03; break;
      case 256: mode = 0x04; break;
      case 1024: mode = 0x05; break;
      default: return;
    }
    if(pin == 5 || pin == 6) {
      TCCR0B = TCCR0B & 0b11111000 | mode;
    } else {
      TCCR1B = TCCR1B & 0b11111000 | mode;
    }
  } else if(pin == 3 || pin == 11) {
    switch(divisor) {
      case 1: mode = 0x01; break;
      case 8: mode = 0x02; break;
      case 32: mode = 0x03; break;
      case 64: mode = 0x04; break;
      case 128: mode = 0x05; break;
      case 256: mode = 0x06; break;
      case 1024: mode = 0x7; break;
      default: return;
    }
    TCCR2B = TCCR2B & 0b11111000 | mode;
  }
}



// ==============================================================================================================
// User Functions/Routines: IR Proximity

/*
  Updates the values of 4 IR proximity sensors. 
  
  Parameters: None
  Returns: None
  
  This function should ONLY use the global variables
    1. ir :: array of "uint16_t" type of size 4. 
        (Refer to chassis diagram)
        ir[0] == IR-Sensor 1
        ir[1] == IR-Sensor 2
        ir[2] == IR-Sensor 3
        ir[3] == IR-Sensor 4
        
    Assigned To: Shruti Phadke
*/
void ir_update(){
}


/*
  Implements an algorithm which decides if system should be put in PROTECTION MODE based on
  4 IR-Proximity sensor readings.
  [Read more about PROTECTION MODE in Programmer's Guide.]
  
  Parameters: None
  Returns: "true" if PROTECTION MODE is to be activated, "false" otherwise. (data type: boolean)
  
  This function should ONLY use the global variables
    1. ir:: 4-length array of type uint16_t 
       Care must be taken as not to change the values of ir[**] in this function.
   
   Assigned To: Shruti Phadke    
*/
boolean ir_protect(){
}


// ==============================================================================================================
// User Functions/Routines: Motor Current Sense and Fail states



/*
  Updates the current values and converts them in milliamperes.
  
  Parameters: None
  Returns: None
  
  This function should ONLY use the global variables
    1. m1_current:: 16-bit integer value representing current in milli-amperes for Motor1
    2. m2_current:: 16-bit integer value representing current in milli-amperes for Motor2
  
  
*/
void   motor_current_update(){
  // Read 10-bit values from ADC
  uint16_t val1 = analogRead(PIN_M1_CS);
  uint16_t val2 = analogRead(PIN_M1_CS);
  
  // Convert values to milliampere
//  m1_current = (uint16_t)((float)(val1 * 5) / (1024.0 * CS_SENSITIVITY));
//  m2_current = (uint16_t)((float)(val2 * 5) / (1024.0 * CS_SENSITIVITY));
    m1_current = val1;
    m2_current = val2;
}


/*
  Updates the failure states for the motor. These are signalled by motor driver's digital pins.
  
  Parameters: None
  Returns: None
  
  This function should ONLY use the global variables
    1. m_failure:: boolean variable, "true" if any of 4 failure pins is LOW.
        [Note: the pins are normally HIGH. In case of failure - are pulled LOW]
        
  Author: Abhishek N. Kulkarni
*/
void  motor_failstate_update(){
/*
  if (digitalRead(PIN_M1_DIAG1) == LOW || digitalRead(PIN_M1_DIAG2) == LOW || digitalRead(PIN_M2_DIAG1) == LOW || digitalRead(PIN_M2_DIAG2) == LOW){
    m_failure = true;
  }
  else{
    m_failure = false;
  }
*/
}


/*
  Implements an algorithm which decides if system should be put in PROTECTION MODE based on
  values of current consumed by individual motors.
  [Read more about PROTECTION MODE in Programmer's Guide.]
  
  Parameters: None
  Returns: "true" if PROTECTION MODE is to be activated, "false" otherwise. (data type: boolean)
  
  This function should ONLY use the global variables
    1. m1_current:: 16-bit integer value representing current in milli-amperes for Motor1
    2. m2_current:: 16-bit integer value representing current in milli-amperes for Motor2
       
*/
boolean motor_currentprotect(){
  return false;
}


// ==============================================================================================================
// User Functions/Routines: Motor Speed GET and SET

/*
  Updates the speed of both motors using the quadrature encoders.
  
  Parameters: None
  Returns: None
  
  This function should ONLY use the global variables
    1. m1_speed:: 16-bit integer value representing the speed of Motor 1 in RPM.
    2. m2_speed:: 16-bit integer value representing the speed of Motor 2 in RPM.
    3. m1_isClockwise:: boolean, "true" if Motor 1 is rotating clockwise, "false" otherwise.
    4. m2_isClockwise:: boolean, "true" if Motor 2 is rotating clockwise, "false" otherwise.
    
  Hint:  
    In general, there are two methods to update the speed.
      A] by measuring the time interval between two consecutive edges.
      B] by measuring the number of edges in pre-defined time interval.
      
    One may write and test the outputs, their reliability in both methods and choose the one which is better.
*/
void  motor_speed_update(){

  /*
    Detailed documentation to be done. But read this.
    
    After considering the minimum and maximum time period to be sensed for motor
    provided the resolution of encoder and min-max speeds of motor, we conclude
    that the frequency method will be best-suited for this application. Note we are
    also constrained by the time-resources on Arduino (64ms WDT).
    
    Slowest Speed Case: 25rpm/170cps/5.88ms      Time periods are of half wave or 1 pulse.
    Fastest Speed Case: 330rpm/2244cps/445us
    
    However, measuring counts, we observe, we may get 1 or 0 counts for slowest case 
    which introduces enourmous quantization error so it's unacceptable.
  */

  boolean pinState;
  uint16_t duration;
  
  //------------------------------------------------------------------------  
  // MOTOR 1
  // Read frequency of pulse on channel A
  duration = pulseIn(PIN_M1_ENCA, HIGH);
  
  // Check Status of channel B: HIGH or LOW and update direction
  pinState = (boolean)digitalRead(PIN_M1_ENCB);
  if (pinState){
    m1_isClockwise = true;
  }
  else{
    m1_isClockwise = false;
  }
  
  // Update the speed of motor using formula --> (1000/time_us) * 60 / 408 
  m1_speed = map(duration, 200, 800, 300, 75);//(uint16_t)(147.0588 / duration);
  
  
  //------------------------------------------------------------------------  
  // MOTOR 2
  // Read frequency of pulse on channel A
  duration = pulseIn(PIN_M2_ENCA, HIGH);
  
  // Check Status of channel B: HIGH or LOW and update direction
  pinState = (boolean)digitalRead(PIN_M2_ENCB);  
  if (pinState){
    m2_isClockwise = true;
  }
  else{
    m2_isClockwise = false;
  }
  
  // Update the speed of motor using formula --> rpm = (1000/time_ms) * 60 / 408 
  m2_speed = map(duration, 200, 800, 300, 75); //(uint16_t)(147.0588 / duration);  
}



/*
  Applies brakes to specified motor. The motor is specified using it's PWM pin.
  
  Parameters:
    1. PIN_LABEL: is one of wrapper(preprocessor definition) for correspondig motor's
        PWM pin.
  
  Return: None
  
  Description: 
    Braking is done using both inputs to high instead of grounding. 
    
  Author: Abhishek Kulkarni
*/
void m_brake(uint8_t PIN_LABEL){
  if (PIN_LABEL == PIN_M1_PWM){
    digitalWrite(PIN_M1_IN1, HIGH);
    digitalWrite(PIN_M1_IN2, HIGH);    
  }
  else if (PIN_LABEL == PIN_M1_PWM){
    digitalWrite(PIN_M2_IN1, HIGH);
    digitalWrite(PIN_M2_IN2, HIGH);    
  }
}

/*
  Starts the motor by setting it's direction.
  
  Parameters:
    1. PIN_LABEL: is one of wrapper(preprocessor definition) for correspondig motor's
        PWM pin.
        
  Returns: None
  
  Author: Abhishek Kulkarni
*/
void m_run(uint8_t PIN_LABEL){
  if (PIN_LABEL == PIN_M1_PWM){
    if (m1_isClockwise){
      digitalWrite(PIN_M1_IN1, HIGH);
      digitalWrite(PIN_M1_IN2, LOW);      
    }
    else{
      digitalWrite(PIN_M1_IN1, LOW);
      digitalWrite(PIN_M1_IN2, HIGH);            
    }
  }
  else if (PIN_LABEL == PIN_M1_PWM){
    if (m2_isClockwise){
      digitalWrite(PIN_M2_IN1, HIGH);
      digitalWrite(PIN_M2_IN2, LOW);      
    }
    else{
      digitalWrite(PIN_M2_IN1, LOW);
      digitalWrite(PIN_M2_IN2, HIGH);            
    }
  }
}


/*
  Reverses the direction of rotation motor.
  
  Parameters:
    1. PIN_LABEL: is one of wrapper(preprocessor definition) for correspondig motor's
        PWM pin.
        
  Returns: None

  Description: 
    If the motor is running, brakes are applied for 100us. And then the switching takes
    place to avoid large instantaneous current through the circuit.
    
  Author: Abhishek Kulkarni
*/
void m_reverse(uint8_t PIN_LABEL){

  if (PIN_LABEL == PIN_M1_PWM){
    if (m1_speed > 0){
      m_brake(PIN_LABEL);    
      delayMicroseconds(BRAKING_DELAY);
    }
    
    if (m1_isClockwise){
      digitalWrite(PIN_M1_IN1, LOW);
      digitalWrite(PIN_M1_IN2, HIGH);      
    }
    else{
      digitalWrite(PIN_M1_IN1, HIGH);
      digitalWrite(PIN_M1_IN2, LOW);            
    }

    m1_isClockwise = ~m1_isClockwise;
    m1_tobeReversed = false;
  }
  else if (PIN_LABEL == PIN_M2_PWM){
    if (m2_speed > 0){
      m_brake(PIN_LABEL);    
      delayMicroseconds(BRAKING_DELAY);
    }
    
    if (m2_isClockwise){
      digitalWrite(PIN_M2_IN1, LOW);
      digitalWrite(PIN_M2_IN2, HIGH);      
    }
    else{
      digitalWrite(PIN_M2_IN1, HIGH);
      digitalWrite(PIN_M2_IN2, LOW);            
    }

    m2_isClockwise = ~m2_isClockwise;
    m2_tobeReversed = false;
  }

}


/*
  Sets the PWM duty cycle of given motor.
  
  Parameters:
    1. PIN_LABEL: is the pin name at which the pwm duty is to be set. Pre-Processor definitions are defined
        which provide verbose names for the pins in terms of Motors (eg. PIN_M1_PWM)
    2. pwmDuty: float:: in range 0-1 to represent the percentage duty cycle to be applied.
   
  Returns: None
  
  This function should ONLY use the global variables
    1. The pre-processor labels defined (optional, but recommended)
    
  Author: Monica Patel (original) , Abhishek Kulkarni (modified)
  Remarks: 
    The frequency is switched according to the PWM duty cycle percentage. 
      0-10%  : signal is grounded -- freewheels
      10-30% : 31Hz frequency
      30-50% : 124Hz frequency
      50-100%: 490Hz frequency
   
*/
void m_setPWM(uint8_t PIN_LABEL, float pwmDuty){
  if ((pwmDuty - 0.0) < 0.001){
    m_brake(PIN_LABEL);
  }
  else{
    m_run(PIN_LABEL);
    if (pwmDuty < 0){
      m_reverse(PIN_LABEL);
      pwmDuty = -pwmDuty;
    }
    
    if (pwmDuty > 0 && pwmDuty <= 0.08){
      analogWrite(PIN_LABEL, 0);
    }
    else if (pwmDuty > 0.08 && pwmDuty <= 0.30){
      setPWMFrequency(PIN_LABEL, 1024);
      analogWrite(PIN_LABEL, (uint8_t)(255 * pwmDuty));
    }
    else if (pwmDuty > 0.30 && pwmDuty <= 0.50){
      setPWMFrequency(PIN_LABEL, 256);
      analogWrite(PIN_LABEL, (uint8_t)(255 * pwmDuty));
    }
    else if (pwmDuty > 0.50 && pwmDuty <= 1.0){
      setPWMFrequency(PIN_LABEL, 64);
      analogWrite(PIN_LABEL, (uint8_t)(255 * pwmDuty));    
    }
    else{
      setPWMFrequency(PIN_LABEL, 64);
      analogWrite(PIN_LABEL, 255);  
    }
  }
}





// ==============================================================================================================
// User Functions/Routines: PID Routine

/*
  Applies correction to current speed of both the motors using PID algorithm.
  
  Parameters: None
  Returns: None
  
  This function should ONLY use the global variables
    1. m1_Kp, m1_Ki, m1_Kd:: float variables representing the P, I, D gains for Motor 1.
    2. m2_Kp, m2_Ki, m2_Kd:: float variables representing the P, I, D gains for Motor 2.
    3. m1_pwm:: 8-bit integer value defining the duty cycle to be given to Motor 1.
    4. m2_pwm:: 8-bit integer value defining the duty cycle to be given to Motor 2.
    5. m1_refSpeed, m1_speed:: 16-bit integer values representing desired speed and current speed of Motor 1. [in RPM]
    6. m2_refSpeed, m2_speed:: 16-bit integer values representing desired speed and current speed of Motor 2. [in RPM]    
*/
void motor_pidCorrect(){
}


// ==============================================================================================================
// User Functions/Routines: ROS Related


// ==============================================================================================================
// User Functions/Routines: Global Level or Common to all


/*
  Implements the protection actions in order to avoid damage to hardware and chassis.
  
  Paramters: 
    1. label:: 8-bit integer, representing the state due to which the PROTECTION MODE was invoked.
      (eg. pre-processor definition: SHORTCIRCUIT implies a failure mode on either of motors was activated.)
      [Read more about PROTECTION MODE in Programmer's Guide.]
  
  Returns: None
  
  Can access any of the global variables. But be careful!!
  
  Hint:
    The function should primarily try to brake the motors systematically, but quickly. Further, it must
    signal the connected device on serial port by transmitting a verbose string explaining about the cause
    which caused the system to go in PROTECTION MODE.
  
*/
void system_protect(uint8_t label){
  
}





// ==============================================================================================================

/*
  Internal Arduino function called once for initialization.
  
  Author: Abhishek N. Kulkarni
*/
void setup() {
  Serial.begin(57600);
//  wdt_enable(WDTO_60MS);
  
  // Pin Configurations
  pinMode(PIN_M1_IN1,   OUTPUT);
  pinMode(PIN_M1_IN2,   OUTPUT);
  pinMode(PIN_M1_PWM,   OUTPUT);
//  pinMode(PIN_M1_DIAG1, INPUT);
//  pinMode(PIN_M1_DIAG2, INPUT);
  pinMode(PIN_M1_ENCA,  INPUT_PULLUP);
  pinMode(PIN_M1_ENCB,  INPUT_PULLUP);
  
  pinMode(PIN_M2_IN1,   OUTPUT);
  pinMode(PIN_M2_IN2,   OUTPUT);
  pinMode(PIN_M2_PWM,   OUTPUT);
//  pinMode(PIN_M2_DIAG1, INPUT);
//  pinMode(PIN_M2_DIAG2, INPUT);
  pinMode(PIN_M2_ENCA,  INPUT_PULLUP);
  pinMode(PIN_M2_ENCB,  INPUT_PULLUP);
  
  
  digitalWrite(PIN_M1_IN1, HIGH);  
  digitalWrite(PIN_M1_IN2, LOW);
  digitalWrite(PIN_M2_IN1, HIGH);
  digitalWrite(PIN_M2_IN2, LOW);  
  
  ir_engage = false;                      //temporary for motor_testing purposes
  m_failure = false;
  PID_Engage = false;
  
  m1_pwm = 0.9;
  m2_pwm = 0.1;  
  
  
  digitalWrite(12, HIGH);
  digitalWrite(A3, LOW);
  digitalWrite(A2, HIGH);
  
  Serial.println("Starting...");
}


/*
  Internal Arduino function called indefinitely unless power-off or reset is applied.
  
  Author: Abhishek N. Kulkarni
*/
void loop() {
  
  // Watchdog-timer reset function
//  wdt_reset();
  
  
  // IR Proximity Sensing, Protection
  ir_update();
  if (ir_engage){
    if (ir_protect()){
      system_protect(NOGROUND);
    }
  }
  Serial.println("IR Updated");
  
  // Motor Current Sense, Protection
  motor_current_update();
  if (motor_currentprotect()){
    system_protect(OVERCURRENT);
  }
  Serial.print("CS1, CS2: ");
  Serial.print(m1_current);
  Serial.print(",");
  Serial.println(m2_current);
  
  // Motor Failure States, Protection
  motor_failstate_update();
  if (m_failure){
    system_protect(SHORTCIRCUIT);
  }
  
  
  // Motor Running-Speed Calculation
  motor_speed_update();
  Serial.print("Speeds (M1, M2): ");
  Serial.print(m1_speed);
  Serial.print(",");
  Serial.println(m2_speed);  
  
  
  // Motor Speed-Update by PID/explicit-PWM
  if (PID_Engage){
    motor_pidCorrect();
  }
  else{
    m_setPWM(PIN_M1_PWM, m1_pwm);
    m_setPWM(PIN_M2_PWM, m2_pwm);
  }
  
  
  // ROS Message Transmit
  delay(1000);
}
