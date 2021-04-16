#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif



enum STATES { S_Wait, S_Press1, S_Press2} S_State;
void Tick(){
   switch(S_State) //transistions
   {
    
   
   
   case SM1_Wait: //wait state
   if(PINA == 0b00){
      S_State = S_Wait;
   }
   else if( ((PINA & 0b01) == 1)  && (PORTB == 0b01) ){
        
        S_State = S_Press1;
   }
   else if( ((PINA & 0b01) == 1)  && (PORTB == 0b10) ){
        S_State = S_Press2;
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
   if(PINA == 0b00;){
   S_State = S_Wait;
   }
   else{
   S_State = S_Press2;  
   }
   break;
   
   default:
   break;
   }
   
   switch(S_State) //State actions  
   {
      case S_Press1:
      PORTB = 0b10;
      break;
      
      case S_Wait: //wait state
      break;
      
      case S_Press2: //incrment state
      PORTB = 0b01;
      break;
           
      default:
      break;

   }
}



int main(void) {
S_State = S_Wait;
Tick();









return 0;
}
