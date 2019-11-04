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

#ifndef EJ3
#define EJ3


  #define F1 80
  #define F2 20
  #define F3 5

  #include <Timer.h>
  #include <Serial.h>
  #include <PWM.h>

  void ej3();


#endif
