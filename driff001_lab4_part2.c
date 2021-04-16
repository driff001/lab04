#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void Tick();

enum S_STATES { S_Wait, S_Press1, S_Press2,S_Press3,S_PressWait} S_State;
void Tick(){
   switch(S_State) //transistions
   {
    case S_Wait: //wait state
        if(PINA == 0b00){
            S_State = S_Wait;
        }
        else if(PINA == 0x01){
            S_State = S_Press1;
        }
        else if( PINA == 0x02){
            S_State = S_Press2;
        }
        else{
            S_State = S_Press3;
        }
        S_State = (PINA == 0x03)? S_Press3 : S_State;
        break;

    case S_Press1: //increment state
        if(PINA == 0b00){
          S_State = S_Wait;
        }
        else if ( PINA == 0b01){
          S_State = S_PressWait;
        }
        else if(PINA == 0x02){
          S_State = S_Press2;
        }
        S_State = (PINA == 0x03)? S_Press3 : S_State;
        break;

    case S_Press2: //decrement state
        if(PINA == 0b00){
        S_State = S_Wait;
        }
        else if ( PINA == 0b10){
          S_State = S_PressWait;
        }
        else if(PINA == 0x01){
          S_State = S_Press1;
        }
        S_State = (PINA == 0x03)? S_Press3 : S_State;
        break;

    case S_Press3: //increment state
        if(PINA == 0b00){
            S_State = S_Wait;
        }
        else if(PINA == 0x01){
            S_State = S_Press1;
        }
        else if( PINA == 0x02){
            S_State = S_Press2;
        }
        else{
            S_State = S_Press3;
        }
        S_State = (PINA == 0x03)? S_Press3 : S_State;
        break;

    case S_PressWait: 
        if (PINA == 0b00){
        S_State = S_Wait;
        }
        else{
        S_State = S_PressWait;
        }
        S_State = (PINA == 0x03)? S_Press3 : S_State;
        break;
   }

   switch(S_State) //State actions
   {
      case S_Press1:
        if (PORTC < 0x09){
        PORTC += 1;
        }
        PORTC = PORTC;
        break;

      case S_Wait: //wait state
        break;

      case S_Press2: //incrment state
        if (PORTC > 0){
        PORTC -= 0b01;
        }
        PORTC = PORTC;
        break;
      case S_Press3: //incrment state
        if (PINA == 0b11){
        PORTC = 0b00;
        }
        break; 

      case S_PressWait:
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
