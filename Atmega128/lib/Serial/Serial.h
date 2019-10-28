#ifndef BASIC
#define BASIC

  #define F_CPU 14745600


  #include <avr/io.h>
  #include <avr/iom128.h>
  #include <avr/interrupt.h>
  #include <string.h>
  #include <stdlib.h>
  
  #define cbi(sfr, bit) (_SFR_BYTE(sfr) &= -_BV(bit))
  #define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
  

#endif

#ifndef SERIAL
#define SERIAL

  void serialInit(unsigned int baud);
  void sendByte(char byte);
  void sendString(char s[]);
  void sendByteSync(char byte);
  void sendStringSync(char s[]);
  void serialTest();

#endif