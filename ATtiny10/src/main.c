// main.c
// ATtiny10
#define		F_CPU   1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void serialRoot();
void pageFW();
void pageBW();
void nextLine();


int main (void)
{
		cli();
		// Set INT0
		EIMSK = 0b00000001;
		EICRA = 0b00000011;
		PUEB = 0b00000101;
		//Set PCINT0
		PCMSK = 0b00000001;
		PCICR = 0b00000001;
		// set PB1 to be output
		DDRB = 0b0000010;
		PORTB = 0b0000010;
		PRR = 0b00000011;
		sei(); // enable interupt
		while (1) {

				SMCR = 0b00000101;
				
		}

		return 1;
}

void nextLine(){
		double delay_iter = 7;
		uint8_t HIGH = 0b00000010;
		uint8_t LOW = 0b00000000;
		// /n
		PORTB = LOW; // Start bit
		_delay_us(delay_iter*2);
		//PORTB = LOW;
		_delay_us(2);
		PORTB = HIGH;
		_delay_us(delay_iter);
		PORTB = LOW;
		_delay_us(delay_iter);
		_delay_us(1);
		PORTB = HIGH;
		_delay_us(delay_iter);
		PORTB = LOW;
		_delay_us(delay_iter*4);
		//PORTB = LOW;
		_delay_us(4);
		//PORTB = LOW;
		//PORTB = LOW;
		PORTB = HIGH; //Stop bit
		_delay_us(delay_iter);
}

void serialRoot(){
		uint8_t HIGH = 0b00000010;
		uint8_t LOW = 0b00000000;
		double delay_iter = 7;
		// r
		PORTB = LOW; // Start bit
		_delay_us(delay_iter);
		PORTB = LOW;
		_delay_us(delay_iter);
		PORTB = HIGH;
		_delay_us(delay_iter);
		_delay_us(1);
		PORTB = LOW;
		_delay_us(delay_iter*2);
		_delay_us(1);
		//PORTB = LOW;
		//_delay_us(delay_iter);
		PORTB = HIGH;
		_delay_us(delay_iter*3);
		//PORTB = HIGH;
		//_delay_us(delay_iter);
		_delay_us(3);
		//PORTB = HIGH;
		//_delay_us(delay_iter);
		PORTB = LOW;
		_delay_us(delay_iter);
		PORTB = HIGH; //Stop bit
		_delay_us(delay_iter);
		// o
		PORTB = LOW; // Start bit
		_delay_us(delay_iter);
		PORTB = HIGH;
		_delay_us(delay_iter*4);
		_delay_us(1);
		//PORTB = HIGH;
		//PORTB = HIGH;
		_delay_us(3);
		//PORTB = HIGH;
		PORTB = LOW;
		_delay_us(delay_iter);
		PORTB = HIGH;
		_delay_us(delay_iter*2);
		_delay_us(3);
		//PORTB = HIGH;
		PORTB = LOW;
		_delay_us(delay_iter);
		PORTB = HIGH; //Stop bit
		_delay_us(delay_iter);
		// o
		PORTB = LOW; // Start bit
		_delay_us(delay_iter);
		PORTB = HIGH;
		_delay_us(delay_iter*4);
		_delay_us(1);
		//PORTB = HIGH;
		//PORTB = HIGH;
		_delay_us(3);
		//PORTB = HIGH;
		PORTB = LOW;
		_delay_us(delay_iter);
		PORTB = HIGH;
		_delay_us(delay_iter*2);
		_delay_us(3);
		//PORTB = HIGH;
		PORTB = LOW;
		_delay_us(delay_iter);
		PORTB = HIGH; //Stop bit
		_delay_us(delay_iter);
		// t
		PORTB = LOW; // Start bit
		_delay_us(delay_iter*3);
		//PORTB = LOW;
		_delay_us(2);
		//PORTB = LOW;
		PORTB = HIGH;
		_delay_us(delay_iter);
		_delay_us(2);
		PORTB = LOW;
		_delay_us(delay_iter);
		PORTB = HIGH;
		_delay_us(delay_iter*3);
		//PORTB = HIGH;
		_delay_us(2);
		//PORTB = HIGH;
		PORTB = LOW;
		_delay_us(delay_iter);
		PORTB = HIGH; //Stop bit
		_delay_us(delay_iter);
		nextLine();
}

void pageFW(){
		SMCR = 0b00000100;
		cli();
		_delay_ms(40);
		while(1){
			uint8_t test = ( PINB & PB2 );
			if (test){	
				break;
				}
		}
		serialRoot();

		uint8_t HIGH = 0b00000010;
		uint8_t LOW = 0b00000000;
		double delay_iter = 7;
		// F
		PORTB = LOW; // Start bit
		_delay_us(delay_iter*2);
		//PORTB = LOW;
		//_delay_us(1);
		PORTB = HIGH;
		_delay_us(delay_iter*2);
		//PORTB = HIGH;
		_delay_us(3);
		PORTB = LOW;
		_delay_us(delay_iter*3+3);
		//PORTB = LOW;
		//PORTB = LOW;
		PORTB = HIGH;
		_delay_us(delay_iter);
		PORTB = LOW;
		_delay_us(delay_iter);
		PORTB = HIGH; //Stop bit
		_delay_us(delay_iter);
		nextLine();
		sei();
}

void pageBW(){
		SMCR = 0b00000100;
		cli();
		_delay_ms(50);
		while(1){
		volatile uint8_t value = ( PINB & ( 1 << PB0 ) ) ? 1 : 0;	
			if (value){	
				break;
				}
		}
		serialRoot();
		double delay_iter = 7;
		// B
		PORTB = 0b00000000; // Start bit
		_delay_us(delay_iter);
		PORTB = 0b00000000;
		_delay_us(delay_iter);
		_delay_us(1);
		PORTB = 0b00000010;
		_delay_us(delay_iter);
		PORTB = 0b00000000;
		_delay_us(delay_iter);
		_delay_us(1);
		PORTB = 0b00000000;
		_delay_us(delay_iter);
		PORTB = 0b00000000;
		_delay_us(delay_iter);
		PORTB = 0b00000000;
		_delay_us(delay_iter);
		_delay_us(1);
		PORTB = 0b00000010;
		_delay_us(delay_iter);
		PORTB = 0b00000000;
		_delay_us(delay_iter);
		PORTB = 0b00000010; //Stop bit
		_delay_us(delay_iter);
		nextLine();
		sei();
}


ISR(INT0_vect){
		pageFW();
}

ISR(PCINT0_vect){
		pageBW();
}

