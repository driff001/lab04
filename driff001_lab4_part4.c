#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void Tick();
int count = 0;
enum S_STATES { S_Wait,S_Lock, S_Press1, S_Press2,S_PressWait1} S_State;
void Tick(){
   switch(S_State) //transistions
   {
    
   
   
   case S_Wait: //wait state
   if( PINA == 0b10000000){
   S_State = S_Lock;
   }
   if(PINA == 0b00){
      S_State = S_Wait;
   }
   else if( PINA == 0b100 ){
        
        S_State = S_Press1;
   }
   else if( (PINA == 0b10)  ){
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
   else if (PINA == 0b01){
   S_State = S_Lock;
   }	   
   else{
   S_State = S_PressWait1;  
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
		   
   case S_PressWait1: 
   if (PINA == 0b00){
   S_State = S_Wait;
   }
   else if(PINA == 0b10){
   S_State = S_Press2;
   }
   else{
   S_State = S_PressWait1;
   }
      
		   
   case S_Lock: //increment state
   break;		  
		   
   default:
   break;
   }
   
   
   switch(S_State) //State actions  
   {
      case S_Press1:
      ++count;
      PORTB = PORTB;
      break;
      
      case S_Wait: //wait state
	
      break;
      
      case S_Press2: //incrment state
      if (count == 1){		   
      PORTB = 0b01;
      }   
      else if (count == 2){
      PORTB = 0b00;
      count = 0;
      }
      PORTB = PORTB;
      break;
     
      case S_Lock:
      PORTB = 0;
      count = 0;
      default:
      break;

   }
}



int main(void) {
S_State = S_Wait;
PORTB = 0b00;
   
 while(1){  
 Tick();
 }



return 0;
}
