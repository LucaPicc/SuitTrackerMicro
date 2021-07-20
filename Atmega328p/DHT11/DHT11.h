
#ifndef DHT11_H_
#define DHT11_H_

    #include <stdio.h>
    #include <avr/io.h>
                                                            
    //setup parameters
    #define DHT_DDR DDRD 
    #define DHT_PORT PORTD
    #define DHT_PIN PIND 
    #define PIN 2
                            
    void DHT11_init(void);
    uint8_t DHT11_read(float *dht_temperature, float *dht_humidity);

#endif /* DHT11_H_ */