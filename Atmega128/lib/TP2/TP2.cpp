#include "TP2.h"
#include<stdio.h> 
#include <Timer.h>
#include <Serial.h>
#include <PWM.h>

#define COMMAND_BUFFER_SIZE 16
#define SHORT_PRESS_CHECKS 5

volatile char commandBuffer[COMMAND_BUFFER_SIZE];

volatile double dc = 100.0;
volatile int freq = F3;

void setFreq(char f){
  switch(f){
    case '0': 
      freq = F1;
      sendStringSync("Cambiando frequencia a 100ms.\n");
      break;
    case '1':
      freq = F2;
      sendStringSync("Cambiando frequencia a 500ms.\n");
      break; 
    case '2':
      freq = F3;
      sendStringSync("Cambiando frequencia a 1000ms.\n");
      break; 
    default:
      sendStringSync("Error 2: Parametros Incorrectos.\n");
  }
}

void sendStatus(){
  char buffer[25];
  sprintf(buffer, "FREQ: %d\nDC: %d\n", freq, (int) dc);
  sendStringSync(buffer);
}

int listenToCommand(){
  int i = 0; 
  int ret = 1;
  char c = '\0';
  while(1){
    c = receiveByte();
    sendByteSync('\0');
    if(c == '\n')
      break;
    if(c != '\0'){
      commandBuffer[i] = c;
      i++;
      if(i >= COMMAND_BUFFER_SIZE){
        i = 0;
        ret = 0;
      }
    }
  }
  commandBuffer[i] = '\0';
  return ret;
}

int parseCommand(){
  char c = commandBuffer[0];
  char *endPtr;
  double arg;
  switch (c){
    case 'e': //ECHO
      if(memcmp(commandBuffer, "echo[", 5) == 0 && strcmp(commandBuffer + 6, "]") == 0){
        sendByteSync(commandBuffer[5]);
        sendByteSync('\n');
        break;
      } else {
        sendStringSync("Error 1: Comando no existe.\n");
      }
    case 's': //SETFREQ SETDC
      if(memcmp(commandBuffer, "set_freq[", 9) == 0 && strcmp(commandBuffer + 10, "]") == 0){
        setFreq(commandBuffer[9]);
      } else if(memcmp(commandBuffer, "set_dc[", 7) == 0){
        arg = strtod(commandBuffer + 7, &endPtr);
        if(strcmp(endPtr, "]") == 0){
          if(arg < 0.0 || arg > 100.0){
            sendStringSync("Error 2: Parametros Incorrectos.\n");
          } else {
            dc = arg;
            sendStringSync("Cambiando DC.\n");
          }
        } else {
          sendStringSync("Error 1: Comando no existe.\n");
        }
      } else {
        sendStringSync("Error 1: Comando no existe.\n");
      }
      break;
    case 'r': //RESET
      if(strcmp(commandBuffer, "reset") == 0){
        dc = 100.0;
        freq = F3;
        sendStringSync("Reseteando.\n");
      } else {
        sendStringSync("Error 1: Comando no existe.\n");
      }
      break;
    default:
      sendStringSync("Error 1: Comando no existe.\n");
      break;
  }
}

volatile int centiSecondsPassed = 0; 
int lightSwitch = 0;
void lightInterruption(){
  centiSecondsPassed++;
  if(centiSecondsPassed > freq){
    if(lightSwitch){
      setPWMDutyCycle(0);
    } else {
      setPWMDutyCycle(dc);
    }
    lightSwitch = !lightSwitch;
    centiSecondsPassed = 0;
  }
}

int pressCount = 0;
void buttonChecker(){
  if(PIND & (1<<PD0)){
    pressCount++;
    if(pressCount > SHORT_PRESS_CHECKS){
      pressCount = SHORT_PRESS_CHECKS + 1;
    }
  } else {
    pressCount = 0;
  }
  if(pressCount == SHORT_PRESS_CHECKS){
    sendStatus();
  } 
}

void tp2(){

    setupTimer0();
    setupPWM();
    serialInit(9600);
    setPWMDutyCycle(dc);
    

    DDRB |= (1 << PORTB7); 
    PORTB |= 0x80;
    setInterval(1,lightInterruption);
    setInterval(1,buttonChecker);

    sendStringSync("ITS ON\n");

    while (1) {
      if(listenToCommand()){
        parseCommand();
        // sendStringSync("Comando: (");
        // sendStringSync(commandBuffer);
        // sendStringSync(")\n");
      }else{
        sendStringSync("Error 0: Comando demaciado largo.\n");
      }
    }
}