#include "Proximity.h"


extern uint16_t IRValues[4];            // Readings of TCRT5000 sensors as 10-bit ADC value
extern float SharpValues[4];            // Readings of SHARP sensors (in ?? <units>)
extern float UltraValues[6];            // Readings of Ultrasonics sensors (in cm)

SharpIR sharp1(PIN_SHARP_1, 25, 93, SHARP_MODEL);
SharpIR sharp2(PIN_SHARP_2, 25, 93, SHARP_MODEL);
SharpIR sharp3(PIN_SHARP_3, 25, 93, SHARP_MODEL);
SharpIR sharp4(PIN_SHARP_4, 25, 93, SHARP_MODEL);


void readIR(){

  // Sense IR No. 1
  digitalWrite(PIN_AM_S2, LOW);
  digitalWrite(PIN_AM_S1, LOW);
  digitalWrite(PIN_AM_S0, LOW);
  delayMicroseconds(5);
  IRValues[0] = analogRead(PIN_AM_Y);
  
  // Sense IR No. 2
  digitalWrite(PIN_AM_S2, LOW);
  digitalWrite(PIN_AM_S1, LOW);
  digitalWrite(PIN_AM_S0, HIGH);
  delayMicroseconds(5);
  IRValues[1] = analogRead(PIN_AM_Y);
  
  // Sense IR No. 3
  digitalWrite(PIN_AM_S2, LOW);
  digitalWrite(PIN_AM_S1, HIGH);
  digitalWrite(PIN_AM_S0, LOW);
  delayMicroseconds(5);
  IRValues[2] = analogRead(PIN_AM_Y);
  
  // Sense IR No. 4
  digitalWrite(PIN_AM_S2, LOW);
  digitalWrite(PIN_AM_S1, HIGH);
  digitalWrite(PIN_AM_S0, HIGH);
  delayMicroseconds(5);
  IRValues[3] = analogRead(PIN_AM_Y);
  
}


float readUltrasonic(uint8_t us_num){
  
  long duration;
  float distance;
  uint8_t echoPin;
  
  switch(us_num){
    case 1: 
      digitalWrite(PIN_DM_S2, LOW);
      digitalWrite(PIN_DM_S1, LOW);
      digitalWrite(PIN_DM_S0, LOW);
      echoPin = PIN_ECHO_US1;
      break;
    
    case 2: 
      digitalWrite(PIN_DM_S2, LOW);
      digitalWrite(PIN_DM_S1, LOW);
      digitalWrite(PIN_DM_S0, HIGH);
      echoPin = PIN_ECHO_US2;
      break;
    
    case 3: 
      digitalWrite(PIN_DM_S2, LOW);
      digitalWrite(PIN_DM_S1, HIGH);
      digitalWrite(PIN_DM_S0, LOW);
      echoPin = PIN_ECHO_US3;
      break;
    
    case 4: 
      digitalWrite(PIN_DM_S2, LOW);
      digitalWrite(PIN_DM_S1, HIGH);
      digitalWrite(PIN_DM_S0, HIGH);
      echoPin = PIN_ECHO_US4;
      break;
    
    case 5: 
      digitalWrite(PIN_DM_S2, HIGH);
      digitalWrite(PIN_DM_S1, LOW);
      digitalWrite(PIN_DM_S0, LOW);
      echoPin = PIN_ECHO_US5;
      break;
    
    case 6: 
      digitalWrite(PIN_DM_S2, HIGH);
      digitalWrite(PIN_DM_S1, LOW);
      digitalWrite(PIN_DM_S0, HIGH);
      echoPin = PIN_ECHO_US6;
      break;
      
  }
  
  delayMicroseconds(5);
  
  digitalWrite(PIN_DM_Y, LOW);  
  delayMicroseconds(2); 
  digitalWrite(PIN_DM_Y, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_DM_Y, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (float)duration/58.2;
  
 if (distance >= 200 || distance <= 0)  {return -1; }
 else                                   { return distance; }
 
}



void ir_update(boolean compensate){
  if (compensate == true){
    /* Sense without LED's: Ambient Noise */
    digitalWrite(PIN_TCRT_LED, LOW);
    readIR();
    
    /* Temporarily copy values */
    uint16_t temp_value[4];
    temp_value[0] = IRValues[0];
    temp_value[1] = IRValues[1];
    temp_value[2] = IRValues[2];
    temp_value[3] = IRValues[3];
    
    /* Sense with LEDs ON: Actual Value */
    digitalWrite(PIN_TCRT_LED, HIGH);
    readIR();
    
    /* Apply compensation */
    IRValues[0] -= temp_value[0];
    IRValues[1] -= temp_value[1];
    IRValues[2] -= temp_value[2];
    IRValues[3] -= temp_value[3];  
  }
  else{
    digitalWrite(PIN_TCRT_LED, HIGH);
    readIR();
  }
}



void ir_protect(){
  // implement later
}



void ultrasonic_update(byte ultra_enable){
  
  if (ultra_enable && (1<<0)){ UltraValues[0] = readUltrasonic(1); }
  if (ultra_enable && (1<<1)){ UltraValues[1] = readUltrasonic(2); }
  if (ultra_enable && (1<<2)){ UltraValues[2] = readUltrasonic(3); }
  if (ultra_enable && (1<<3)){ UltraValues[3] = readUltrasonic(4); }
  if (ultra_enable && (1<<4)){ UltraValues[4] = readUltrasonic(5); }
  if (ultra_enable && (1<<5)){ UltraValues[5] = readUltrasonic(6); }
  
}


void sharp_update(byte sharp_enable){
  if(sharp_enable && (1<<0) == 1)
  {
    SharpValues[0] = sharp1.distance();
  }
  
  if(sharp_enable && (1<<1) == 1)
  {
    SharpValues[1] = sharp2.distance();
  }
  
  if(sharp_enable && (1<<2) == 1)
  {
    SharpValues[2] = sharp3.distance();
  }
  
  if(sharp_enable && (1<<3) == 1)
  {
    SharpValues[3] = sharp4.distance();
  }
}
