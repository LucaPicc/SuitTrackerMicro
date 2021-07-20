#include "DHT11.h"
#include "../USART/USART.h"
#include <stdlib.h>
#include "util/delay.h"

void DHT11_init(void){
    DHT_DDR |= (1<<PIN);    //PIN out
    DHT_PORT |= (1<<PIN);   //PIN HIGH
    USART_init();
}

/*
        18us      (20 or 40)us     80us       80us
    |___________|''''''''''''''|___________|''''''''''|-----datos----
    |-----------328p-----------|---------------DHT11-----------------    
*/

/*
    Data:
               1byte   1byte    1byte    1byte    1byte
            |--------|--------|--------|--------|--------|
            |     humidity    |   temperature   |  check |

        pulse:
                50us      26-28 or 70 us
            |____________|'''''''''''''''|

            if pulse width between 26 28us, byte is low
            if pulse width is major 28 us, byte is hight 
*/

uint8_t DHT11_read(float *dht_temperature, float *dht_humidity){
    uint8_t bits[5];
    uint8_t i, j, count = 0;
    char l[20];

    // Send pulse with low by 18 ms

    DHT_PORT &= ~(1<<PIN);
    _delay_ms(18);

    // We changed PIN as input and state as HIGH

    DHT_PORT |= (1<<PIN);   //PIN HIGH
    DHT_DDR &= ~(1<<PIN);    //PIN input

    // We wait for the pin to change to low 20us to 40us

    while (DHT_PIN & (1<<PIN))
    {
        _delay_us(2);
        count += 2;
        if (count > 80){
            DHT_DDR |= (1<<PIN);    //PIN out
            DHT_PORT |= (1<<PIN);   //PIN HIGH
            return 0;
        }
    }

    //USART_putstring('Sali\n');

    // We wait for the pin to change to high by 80us
    count = 0;
    while (!(DHT_PIN & (1<<PIN)))
    {
        _delay_us(2);
        count += 2;
        if (count > 100){
            DHT_DDR |= (1<<PIN);    //PIN out
            DHT_PORT |= (1<<PIN);   //PIN HIGH
            return 0;
        }
    }

    //USART_putstring('Sali\n');


    // We wait for the pin to change to high by 80us
    count = 0;
    while (DHT_PIN & (1<<PIN))
    {
        _delay_us(2);
        count += 2;
        if (count > 100){
            DHT_DDR |= (1<<PIN);    //PIN out
            DHT_PORT |= (1<<PIN);   //PIN HIGH
            return 0;
        }
    }

    //USART_putstring('Sali\n');

    // We read 40 bits

    for( j=0;j<4;j++)
    {
        uint8_t result = 0;
        for(i=0; i<7; i++)
        {
            while (!(DHT_PIN & (1<<PIN)));
            
            _delay_us(30);

            if(DHT_PIN & (1<<PIN)){
                result |= (1<<(7-i));
            }

            while (DHT_PIN & (1<<PIN));
            
        }
        bits[j] = result;
    }

    DHT_DDR |= (1<<PIN);    //PIN out
    DHT_PORT |= (1<<PIN);   //PIN HIGH

    // Convert

    if((uint8_t)(bits[0] + bits[1] + bits[2] + bits[3]) == bits[4]){
        uint16_t rawhumidity = bits[0]<<8 | bits[1];
        uint16_t rawtemperature = bits[2]<<8 | bits[3]; 
        
        USART_putstring("RAW TEMP:\t");
        dtostrf(rawtemperature,8,0,l);
        USART_putstring(l);
        USART_putstring("\n");

        USART_putstring("RAW HUM:\t");
        dtostrf(rawhumidity,8,0,l);
        USART_putstring(l);
        USART_putstring("\n");



        *dht_temperature = (float)(rawtemperature)/10;
        *dht_humidity = (float)(rawhumidity)/10;

        return 1;
    }

    return 0;

}
