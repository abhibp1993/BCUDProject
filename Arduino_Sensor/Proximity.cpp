#include "Proximity.h"




//void ir_update(boolean compensate){
//  
//  
//}

void ir_update(byte enable, uint16_t* arrVal){

  arrVal[0]=analogRead(TCRT_0);
  arrVal[1]=analogRead(TCRT_1);
  arrVal[2]=analogRead(TCRT_2);
  arrVal[3]=analogRead(TCRT_3);
}

void ir_protect(){
  
}



void ultrasonic_update(byte ultra_enable){
  
}
