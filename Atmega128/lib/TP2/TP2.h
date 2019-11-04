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

#ifndef TP2
#define TP2

  #define F1 10
  #define F2 50
  #define F3 100

  void tp2();

#endif