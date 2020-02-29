
# Librerias Atmega128 (Introducción a Sistemas Embebidos ITBA 2019) 

En la carpeta Atmega128 se encuentra mi proyecto generado con la extensión platformIO de VSCode (La recomiendo fuerte, en especial si usas windows).
El main se encuentra en ./Atmega128/src/main.cpp y los drivers en ./Atmega128/lib/

* Datasheets:
  * [Atmega128](http://ww1.microchip.com/downloads/en/DeviceDoc/doc2467.pdf)
  * [Crumb (El integrado usado por la catedra)](https://www.chip45.com/download/Crumb128-CAN_V5.0-5.1_infosheet.pdf)
* [Videotutoriales que valen la pena (humanHardDrive)](https://www.youtube.com/playlist?list=PLA6BB228B08B03EDD)
* [AVR toolchain en windows](http://fab.cba.mit.edu/classes/863.16/doc/projects/ftsmin/windows_avr.html)
* Serial Port en Windows 10:
  * [Driver](https://www.denso-wave.com/en/adcd/download/category/soft-driver/qb/Active-USB-COM.html)
  * [Tera Term](https://ttssh2.osdn.jp/index.html.en)

## Entrega de los TPs:
El main se encuentra en ./Atmega128/src/main.cpp
Las drivers y librerias con los ejercicios en ./Atmega128/lib/
Hay que descomentar en el main, la funcion con el ejercicio que se quiera compilar.

### Mas info sobre TP3:
- Uso interrupciones para hacer las lecturas.
- Tengo un metodo [void selectMuxChannel(int chan)] que recibe el numero de pin de donde leer el ADC y selecciona el PFn correspondiente.
- Uso el PF1 (ADC1) para leer el la resistencia variable (crank) y uso el PF2 (ADC2) para leer el termometro (thermistor)
- Uso la ecuacion de Steinhart-Hart para calcular la temperatura en celcius en base al termistor. 
El metodo [double getTemp(int val)] lo saque de https://www.electronicwings.com/avr-atmega/thermistor-interfacing-with-atmega1632


### Mejoras que aun se pueden hacer:
- Mover el codigo de setupADC, la interrupcion, startConversion y selectMuxChannel a una libreria que se llame ADC.h. 
Podria hacer setup de que pines quiero leer, la interrupcion rotar la lectura de los mismos y guardar los valores en un array de shorts o ints 
y luego hacer un short getADCValue(int channel).