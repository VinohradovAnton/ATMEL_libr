
#ifndef DHT11_H_
#define DHT11_H_

#include <stdio.h>
#include <avr/io.h>

//setup parameters
#define DHT11_DDR DDRC
#define DHT11_PORT PORTC
#define DHT11_PIN PINC
#define DHT11_INPUTPIN PC5

extern int8_t dht11_gettemperature();
extern int8_t dht11_gethumidity();

#endif
