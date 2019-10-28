
#include <Ej1.h>
// #include <Ej2.h>
// #include <Ej3.h>
// #include <Ej4.h>
#include <Serial.h>
#include <Timer.h>

void switcher(){
  
  setupTimer0();
  serialInit(9600);

  DDRB |= (1 << PORTB7);  //B4 output
  DDRD = 0x00; //Makes all pins of PORTD input
  PORTD = 0x00;
  int pressCount = 0;
  while(1) //infinite loop
  {
    if(PIND & (1<<PD0)){
      pressCount++;
      // sendStringSync("A");
    } else {
      pressCount = 0;
      // sendStringSync("B");
    }
    if(pressCount >= 10){
      PORTB |= (1<<PB7);
      pressCount = 10;
    } else {
      PORTB &= ~(1<<PB7);
    }
  }
}

int main(void)
{
    switcher();
    // ej1();
    // ej2();
    // ej3();
    // ej4();
    // serialTest();

    return 0;
}
