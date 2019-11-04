#include "Ej2.h"


#define F1 800
#define F2 200
#define F3 50


void setPWMMode(int mode){
  switch(mode){
    case 0:
      setPWMDutyCycle(10);
      sendStringSync("0");
      break;
    case 1:
      sendStringSync("1");
      setPWMDutyCycle(50);
      break;
    case 2:
      sendStringSync("2");
      setPWMDutyCycle(80);
      break;
  }
}

int buttonPushCounter = 0;   
int buttonState = 0;  
int lastButtonState = 0; 

void ej2(){

  setupTimer0();
  serialInit(9600);
  setupPWM();

  DDRB |= (1 << PORTB7);  //B4 output
  DDRD = 0x00; //Makes all pins of PORTD input
  PORTD = 0x00;

  int pressCount = 0;
  while(1){
    if(PIND & (1<<PD0)){
      pressCount++;
    } else {
      pressCount = 0;
    }
    if(pressCount >= 10){
      buttonState = 1;
      pressCount = 10;
    } else {
      buttonState = 0;
      lastButtonState = 0;
    }

    if (buttonState == 1 && buttonState != lastButtonState) {
      lastButtonState = 1;
      buttonPushCounter++;
    }
    setPWMMode(buttonPushCounter % 3);
  }
}