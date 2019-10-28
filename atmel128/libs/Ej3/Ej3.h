#ifndef EJ1
#define EJ1

  #define F_CPU 14745600
  #define F1 80
  #define F2 20
  #define F3 5

  #include <avr/io.h>
  #include <avr/iom128.h>
  #include <avr/interrupt.h>

  void delay(int centiSecondsWait);
  void setupTimer0();
  void setupPWM();
  void setPWMDutyCycle(int percent);
  void ej3();

#endif