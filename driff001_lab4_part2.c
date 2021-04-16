#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void Tick();
enum S_STATES { S_Wait, S_Press1, S_Press2,S_Press3} S_State;
void Tick(){
   switch(S_State) //transistions
   {
    
   
   
   case S_Wait: //wait state
   if(PINA == 0b00){
      S_State = S_Wait;
   }
   else if( ((PINA & 0b01) == 1)  && (PORTC < 0b1001) ){
        
        S_State = S_Press1;
   }
   else if( ((PINA & 0b10) == 1)  && (PORTC > 0b00) ){
        S_State = S_Press2;
   }
   else if( (PINA & 0b11) == 1 ){
   	S_State = S_Press3;
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
   
   case S_Press3: //increment state
   if(PINA == 0b00){
   S_State = S_Wait;
   }
   else{
   S_State = S_Press3;
   }
	
   default:
   break;
   }
   
   switch(S_State) //State actions  
   {
      case S_Press1:
      PORTC += 0b01;
      break;
      
      case S_Wait: //wait state
      break;
      
      case S_Press2: //incrment state
      PORTC -= 0b01;
      break;
      
      case S_Press2: //incrment state
      PORTC = 0b00;
      break;
        
      default:
      break;

   }
}



int main(void) {
S_State = S_Wait;
PORTC = 0b111;
   
 while(1){  
 Tick();
 }



return 0;
}