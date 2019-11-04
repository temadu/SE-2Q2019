#include "Ej1.h"
#include <Timer.h>
#include <Serial.h>
#include <PWM.h>

void ej1(){

    setupTimer0();
    serialInit(9600);
    
    setupPWM();

    DDRB |= (1 << PORTB7); 
    PORTB |= 0x80;

    while (1) {
        setPWMDutyCycle(10.0);
        delay(100);
        setPWMDutyCycle(100.0);
        delay(100);
    }
}