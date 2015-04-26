#include "Proximity.h"

void ir_update(uint16_t* arrVal){

  arrVal[0] = analogRead(TCRT_0);
  arrVal[1] = analogRead(TCRT_1);
  arrVal[2] = analogRead(TCRT_2);
  arrVal[3] = analogRead(TCRT_3);
}

void ir_protect(){
  
}



float ultrasonic_update(){
  
  float dist = 0.0;
  uint16_t duration = 0;
  
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG_US1, LOW);  
  delayMicroseconds(2); 
  digitalWrite(PIN_TRIG_US1, HIGH);
  delayMicroseconds(10);
  digitalWrite(PIN_TRIG_US1, LOW);
  
  duration = pulseIn(PIN_ECHO_US1, HIGH);
  dist = (float)duration/58.2;
  
 if (dist >= 200 || dist <= 0)  {return -1; }
 else                           { return dist; }
}
