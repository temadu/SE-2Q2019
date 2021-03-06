#include "Ej3.h"

volatile int centiSecondsPassed = 0; 
volatile int centiSecondsToWait = 10; 
volatile int changerCentiSeconds = 0; 

volatile int buttonPushCounter = 0;   
volatile int buttonState = 0;  
volatile int lastButtonState = 0; 

void lightFrecuencyInterruption(){
  centiSecondsPassed++;
  if (PIND & (1<<PD0)){
    changerCentiSeconds++;
  } else {
    changerCentiSeconds = 0;
  }
  if(centiSecondsPassed > centiSecondsToWait){
    PORTB ^= (1 << PORTB7);
    centiSecondsPassed = 0;
  }
}

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

int pwmModeCounter = 0;
int lightIntesityCheck = 0;
void lightIntensityInterruption(){
  if(lightIntesityCheck == 1 && (PIND & (1<<PD0))){
    pwmModeCounter++;
    if(pwmModeCounter > 2){
      pwmModeCounter = 0;
    }
    setPWMMode(pwmModeCounter);
  }
  
  if (PIND & (1<<PD0)){
    lightIntesityCheck++;
    if(lightIntesityCheck >= 2){
      lightIntesityCheck = 2;
    }
  } else {
    lightIntesityCheck = 0;
  }
}

void ej3(){

  setupTimer0();
  serialInit(9600);
  // setupPWM();

  DDRB |= (1 << PORTB7); 
  PORTB |= 0x80;
  DDRD = 0x00; //Makes all pins of PORTD input
  PORTD = 0x00;

  setInterval(1,lightFrecuencyInterruption);

  while(1){

    if(changerCentiSeconds >= 100){
      buttonPushCounter++;
      if(buttonPushCounter > 2){
        buttonPushCounter = 0;
      }
      changerCentiSeconds = 0;
    }

    if(buttonPushCounter == 0){
      centiSecondsToWait = 10;
    } else if (buttonPushCounter == 1){
      centiSecondsToWait = 50;
    } else {
      centiSecondsToWait = 100;
    }

  }
}
