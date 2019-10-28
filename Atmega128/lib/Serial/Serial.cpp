#include "Serial.h"
#include <Timer.h>


#define TX_BUFFER_SIZE 128
#define RX_BUFFER_SIZE 128

char txBuffer[TX_BUFFER_SIZE];
char rxBuffer[RX_BUFFER_SIZE];

uint8_t txReadPos = 0;
uint8_t txWritePos = 0;

uint8_t rxReadPos = 0;
uint8_t rxWritePos = 0;

void serialInit( unsigned int baud){
  unsigned int ubrr = ((F_CPU/16/baud)-1);
  SREG|=0x80;
  /* Set baud rate */
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0) | (1<<RXCIE0) | (1<<TXEN0) | (1<<TXCIE0);
  /* Set frame format: 8data, 1stop bit */
  UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);

}

void USART_TX( unsigned char data ){
  while ( !( UCSR0A & (1<<UDRE0)) );
  UDR0 = data;
}
char USART_RX(){
  while(!(UCSR0A & (1<<RXC0)));
  return UDR0;
}

void appendTXBuffer(char c){
  txBuffer[txWritePos] = c;
  txWritePos++;
  if(txWritePos >= TX_BUFFER_SIZE){
    txWritePos = 0;
  }
}

void sendByte(char byte){
  appendTXBuffer(byte);
  if( UCSR0A & (1<<UDRE0)){
    UDR0 = 0;
  }
}

void sendString(char s[]){
  for(unsigned int i = 0; i < strlen(s); ++i){
    appendTXBuffer(s[i]);
  }
  if( UCSR0A & (1<<UDRE0)){
    UDR0 = 0;
  }
}

void sendByteSync(char byte){
  USART_TX(byte);
}

void sendStringSync(char s[]){
  for(unsigned int i = 0; i < strlen(s); ++i){
    USART_TX(s[i]);
  }
}

char receiveByteSync(){
  return USART_RX();
}
void receiveStringSync(){
  char r[32];
  int i = 0;

  // for(unsigned int i = 0; i < strlen(s); ++i){
  //   USART_TX(s[i]);
  // }
}

char receiveByte(){
  char ret = '\0';
  if(rxReadPos != rxWritePos){
    ret = rxBuffer[rxReadPos];
    rxReadPos++;
    if(rxReadPos >= RX_BUFFER_SIZE){
      rxReadPos = 0;
    }
  }
  return ret;
}
char arr[10];
int i = 0; 

void tester1(){
  // sendString("Testerinos\n\r");
  // PORTB ^= 0x80;
  sendStringSync(arr);
  sendStringSync(".\n\r");
}

void serialTest(){

    setupTimer0();
    serialInit(9600);

    DDRB |= (1 << PORTB7); 
    PORTB = 0x00;

    setInterval(100,tester1);
    // delay(50);
    // setInterval(50,tester2);
    

    while (1){
      char c = receiveByte();
      if(c != '\0'){
        arr[i] = c;
        i++;
        if(i >= 10){
          i = 0;
        }
      }
      if(c=='0'){
        // PORTB |= 0xFF;
        sbi(PORTB, PORT0);
      } else if (c=='1'){
        // PORTB &= 0x00;
        cbi(PORTB, PORT0);
      }
    }
}

ISR(USART0_TX_vect){
  if(txReadPos != txWritePos){
    UDR0 = txBuffer[txReadPos];
    txReadPos++;
    if(txReadPos >= TX_BUFFER_SIZE){
      txReadPos = 0;
    }
  }
}

ISR(USART0_RX_vect){
  rxBuffer[rxWritePos] = UDR0;
  rxWritePos++;

  if(rxWritePos >= RX_BUFFER_SIZE){
    rxWritePos = 0;
  }
}