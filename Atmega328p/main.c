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
	float temperature, humidity;
	uint8_t status;
	
	DHT11_init();
	USART_init();

	/* DDRB |= (1<<DDB5);
	PORTB |= (1<<PORTB5); */


	while (1){
		
		status = DHT11_read(&temperature, &humidity);

		if(status==1){
			dtostrf(temperature,2,2,String);
			
			USART_putstring("Temperatura:\t");
			USART_putstring(String);
			//USART_putstring("C");
			USART_putstring("\n");
			
			dtostrf(humidity,2,2,String);
			
			USART_putstring("Humedad:\t");
			USART_putstring(String);
			//USART_putstring("%");
			USART_putstring("\n");	
		}else{
			USART_putstring("ERROR!!!\n");
		}
		
		_delay_ms(2000);
	}

	return 0;
}