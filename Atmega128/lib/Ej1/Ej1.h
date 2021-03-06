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

#ifndef EJ1
#define EJ1

  #define F1 80
  #define F2 20
  #define F3 5

  void setupPWM();
  void setPWMDutyCycle(int percent);
  void ej1();

#endif