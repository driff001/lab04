nclude <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void Tick();

enum S_STATES { S_Wait,S_Lock S_Press1, S_Press2} S_State;
void Tick(){
   switch(S_State) //transistions
   {
    
   
   
   case S_Wait: //wait state
   if(PINA == 0b00){
      S_State = S_Wait;
   }
   if( PINA == 0b10000000){
   S_State = S_Lock;
   }

   if( (PINA & 0b100) == 4 ){
        
        S_State = S_Press1;
   }
   else if( (PINA & 0b10) == 2)  && (count == 1) ){
        S_State = S_Press2;
   }
   else {
        S_State = S_Lock;
   }   
   break;
   
   case S_Press1: //increment state
   if(PINA == 0b00){
   S_State = S_Wait;
   }
   else{
   S_State = S_Press1;  
   }
   break;
   
   case S_Press2: //decrement state
   if(PINA == 0b00){
   S_State = S_Wait;
   }
   else{
   S_State = S_Press2;  
   }
   break;
   
   default:
   break;
   }
   case S_Lock: //increment state
   if(PINA == 0b00){
   S_State = S_Wait;
   }
   else{
   S_State = S_Lock;
   }
   
   switch(S_State) //State actions  
   {
      case S_Press1:
      ++count;
      break;
      
      case S_Wait: //wait state
	
      break;
      
      case S_Press2: //incrment state
      PORTB = 0b01;
      count = 0;
      break;
     
      case S_Lock:
      B = 0;
      count = 0;
      default:
      break;

   }
}



int main(void) {
S_State = S_Wait;
PORTB = 0b01;
   
 while(1){  
 Tick();
 }



return 0;
}
