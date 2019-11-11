#include "TP3.h"
#include<stdio.h> 
#include <math.h>
#include <Timer.h>
#include <Serial.h>
#include <PWM.h>

#define COMMAND_BUFFER_SIZE 16
#define SHORT_PRESS_CHECKS 5

volatile char commandBuffer[COMMAND_BUFFER_SIZE];

volatile int crankValue = 0;
volatile int thermValue = 0;

double getDecimal(double num){
 return ((num-(int)num)*10);
}

double getTemp(int val){
	long R=((10230000/val) - 10000);/* calculate the resistance */
	double Thermister = log(R);	/* calculate natural log of resistance */
	/* Steinhart-Hart Thermistor Equation: */
	/*  Temperature in Kelvin = 1 / (A + B[ln(R)] + C[ln(R)]^3)		*/
	/*  where A = 0.001129148, B = 0.000234125 and C = 8.76741*10^-8  */
	Thermister = 1 / (0.001129148 + (0.000234125 * Thermister) + (0.0000000876741 * Thermister * Thermister * Thermister));
	Thermister = Thermister - 273.15;/* convert kelvin to °C */
	
	return Thermister;
}

void sendStatus(){
  char buffer[50];
  double crankCalc = (crankValue*5.0)/1024.0;  
  double thermCalc = getTemp(thermValue);  
  sprintf(buffer, "crankADC: %d, crankVolt: %d.%d%d V\n", crankValue, (int) crankCalc, (int) getDecimal(crankCalc), (int) getDecimal(getDecimal(crankCalc)));
  sendStringSync(buffer);
  sprintf(buffer, "thermADC: %d, temperature: %d.%d%d Celsius\n", thermValue, (int) thermCalc, (int) getDecimal(thermCalc), (int) getDecimal(getDecimal(thermCalc)));
  sendStringSync(buffer);
  sendStringSync("\n");
}

void startConversion(){
  ADCSRA |= (1 << ADSC);
}

void selectMuxChannel(int chan){
  ADMUX = (ADMUX & 0xE0) | (chan & 0x1F);   //select channel (MUX0-4 bits)
}

void setupADC(){
  ADMUX |= (1 << REFS0); //USAR AVCC como ref (5volts)
  ADCSRA |= (1 << ADEN) | (1 << ADIE); //Start && interrupt mode
  ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); //Prescaler to 128
  selectMuxChannel(1);
  startConversion();
  sei();
}


void tp3(){

    setupTimer0();
    serialInit(9600);
    setupADC();
    DDRB |= (1 << PORTB7); 
    PORTB |= 0x80;

    setInterval(100,sendStatus);
    
    while (1);
}

volatile signed char isCrank = 0;
ISR(ADC_vect){
  if(isCrank){
    crankValue = ADC;
    selectMuxChannel(2);
  }else{
    selectMuxChannel(1);
    thermValue = ADC;
  }
  isCrank = !isCrank;
  startConversion();
}