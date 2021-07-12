
#ifndef DHT11_H_
#define DHT11_H_

#include <stdio.h>
#include <avr/io.h>
                                                        
//setup parameters
#define DHT_DDR DDRB 
#define DHT_PORT PORTB
#define DHT_PIN PINB 
#define PIN PB0
                         
void DHT11_init(void);
uint8_t DHT11_read(float *dht_temperature, float *dht_humidity)

#endif