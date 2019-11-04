#include "Ej4.h"

int switcher = 0;
void turner(){
  PORTB ^= (1<<PB7);
  // if(switcher){
  //   setPWMDutyCycle(0.0);
  // }else {
  //   setPWMDutyCycle(60.0);
  // }
  // switcher != switcher;
}

void ej4(){

    setupTimer0();
    // serialInit(9600);
    
    // setupPWM();

    DDRB |= (1 << PORTB7); 
    PORTB |= 0x80;
    setInterval(100,turner);

    while (1);
}