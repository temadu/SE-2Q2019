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

#ifndef TIMER
#define TIMER

  void setupTimer0();
  long getCentiseconds();
  void delay(int centiSecondsWait);
  int setInterval(long centiSeconds, void (*callback)(void));
  void clearInterval(int id);

#endif