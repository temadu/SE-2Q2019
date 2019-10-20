#ifndef EJ1
#define EJ1

  #define F_CPU 14745600
  #define F1 800
  #define F2 200
  #define F3 50

  #include <avr/io.h>
  #include <avr/iom128.h>
  #include <avr/interrupt.h>
  #include <util/delay.h>

  void blink();
  void switcher();
  void setupTimer0();
  void setupPWM();
  void setPWMDutyCycle(int percent);
  void blinkWithOurTimer();

#endif