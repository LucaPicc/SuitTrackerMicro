#include <avr/io.h>
//#define F_CPU 16000000U
#include "util/delay.h"
#include <avr/interrupt.h>
#include "USART/USART.h"
#include "DHT11/DHT11.h"

#include <stdlib.h>

char String[10] = "HOla";
char interrupcion = 0;




int main(){
	
	uint8_t rawhumidity,rawtemperature;
	float temperature, humidity;
	char bufor[8]; 

	USART_init();
	DDRB |= (1<<DDB5);
	PORTB |= (1<<PORTB5);


	while (1){
		
		rawtemperature = dht11_gettemperature;
		temperature = (float)(rawtemperature)/10.0;
		rawhumidity = dht11_gethumidity;
		rawhumidity = (float)(rawhumidity)/10.0;

		dtostrf(rawtemperature,2,2,String);
		USART_putstring("Temperatura:\t");
		USART_putstring(String);
		//USART_putstring("C");
		USART_putstring("\n");
		
		dtostrf(rawhumidity,2,2,String);
		USART_putstring("Humedad:\t");
		USART_putstring(String);
		//USART_putstring("%");
		USART_putstring("\n");	
		
		_delay_ms(2000);
	}


	return 0;
}