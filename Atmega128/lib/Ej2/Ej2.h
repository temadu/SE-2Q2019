#ifndef EJ2
#define EJ2

  #define F_CPU 14745600
  #define F1 800
  #define F2 200
  #define F3 50

  #include <avr/io.h>
  #include <avr/iom128.h>
  #include <avr/interrupt.h>

  void setupPWM();
  void setPWMDutyCycle(int percent);
  void setPWMMode(int mode);
  void ej2();


#endif