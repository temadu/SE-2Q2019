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

#ifndef TP3
#define TP3

  void tp3();

#endif