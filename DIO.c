/*
 * DIO.c
 *
 * Created: 10/2/2023 8:46:24 PM
 *  Author: M Osama
 */ 


#include <avr/io.h>
#include "DIO.h"
/*pins*/
void DIO_pin_dierction (ports port ,pins pin ,directions direction){
	switch (port)
	{
		case DIO_PORTA:
	if (direction == DIO_OUTPUT) { SET_BIT(DDRA,pin); }
else{ CLR_BIT(DDRA,pin); }
break;
case DIO_PORTB:
			if (direction == DIO_OUTPUT) { SET_BIT(DDRB,pin); }
			else{ CLR_BIT(DDRB,pin); }
			break;
		case DIO_PORTC:
			if (direction == DIO_OUTPUT) { SET_BIT(DDRC,pin); }
			else{ CLR_BIT(DDRC,pin); }
			break;
		case DIO_PORTD:
			if (direction == DIO_OUTPUT) { SET_BIT(DDRD,pin); }
			else{ CLR_BIT(DDRD,pin); }
			break;
		default: break;	
	}
		
	
}

void DIO_pin_write (ports port ,pins pin ,unsigned char val){
	switch (port)
	{
		case DIO_PORTA:
			if (val == 1) { SET_BIT(PORTA,pin); }
			else{ CLR_BIT(PORTA,pin); }
			break;
		case DIO_PORTB:
			if (val == 1) { SET_BIT(PORTB,pin); }
			else{ CLR_BIT(PORTB,pin); }
			break;
		case DIO_PORTC:
			if (val == 1) { SET_BIT(PORTC,pin); }
			else{ CLR_BIT(PORTC,pin); }
			break;
		case DIO_PORTD:
			if (val == 1) { SET_BIT(PORTD,pin); }
			else{ CLR_BIT(PORTD,pin); }
			break;
		default: break;	
	}	
	
}

unsigned char DIO_pin_read (ports port ,pins pin ){
	unsigned char ret = 0;
	switch (port)
	{
		case DIO_PORTA:
			ret = READ_BIT(PINA,pin);
			break;
		case DIO_PORTB:
			ret = READ_BIT(PINB,pin);
			break;
		case DIO_PORTC:
			ret = READ_BIT(PINC,pin);
			break;
		case DIO_PORTD:
			ret = READ_BIT(PIND,pin);
			break;
		default: break;	
	}	
	return ret;
}

void DIO_pin_toggle (ports port ,pins pin ){
	switch (port)
	{
		case DIO_PORTA:
			TOG_BIT(PORTA,pin);
		break;
		case DIO_PORTB:
			TOG_BIT(PORTB,pin);
		break;
		case DIO_PORTC:
			TOG_BIT(PORTC,pin);
		break;
		case DIO_PORTD:
			TOG_BIT(PORTD,pin);
		break;
		default: break;
	}	
	
}

/*ports*/
void DIO_port_dierction (ports port ,unsigned char direction){
	switch (port)
	{
		case DIO_PORTA:
			DDRA = direction;
			break;
		case DIO_PORTB:
			DDRB = direction;
			break;
		case DIO_PORTC:
			DDRC = direction;
			break;
		case DIO_PORTD:
			DDRD = direction;
			break;
		default: break;
	}	
	
}

void DIO_port_write (ports port ,unsigned char val){
	switch (port)
	{
		case DIO_PORTA:
			PORTA = val;
			break;
		case DIO_PORTB:
			PORTB = val;
			break;
		case DIO_PORTC:
			PORTC = val;
			break;
		case DIO_PORTD:
			PORTD = val;
			break;
		default: break;
	}	
	
}

unsigned char DIO_port_read (ports port){
	unsigned char ret = 0;
	
	switch (port)
	{
		case DIO_PORTA:
			ret = PINA;
			break;
		case DIO_PORTB:
			ret = PINB;
			break;
		case DIO_PORTC:
			ret = PINC;
			break;
		case DIO_PORTD:
			ret = PIND;
			break;
		default: break;
	}	
	
}


void DIO_connectPullUP(ports port ,pins pin, connection connect){
	switch (port)
	{
		case DIO_PORTA:
			if (connect == PULLUP_CONNECT) { SET_BIT(PORTA,pin); }
			else{ CLR_BIT(PORTA,pin); }
			break;
		case DIO_PORTB:
			if (connect == PULLUP_CONNECT) { SET_BIT(PORTB,pin); }
			else{ CLR_BIT(PORTB,pin); }
			break;
		case DIO_PORTC:
			if (connect == PULLUP_CONNECT) { SET_BIT(PORTC,pin); }
			else{ CLR_BIT(PORTC,pin); }
			break;
		case DIO_PORTD:
			if (connect == PULLUP_CONNECT) { SET_BIT(PORTD,pin); }
			else{ CLR_BIT(PORTD,pin); }
			break;
		default: break;	
	}
	
}

void write_low_nibble(ports portname,unsigned char value){
	value&=0x0f;
	switch(portname)
	{
		case DIO_PORTA:
			PORTA&=0xf0;
			PORTA|=value;
		break;
		case DIO_PORTB:
			PORTB&=0xf0;
			PORTB|=value;
		break;
		case DIO_PORTC:
			PORTC&=0xf0;
			PORTC|=value;
		break;
		case DIO_PORTD:
			PORTD&=0xf0;
			PORTD|=value;
		break;
	}
	
}
void write_high_nibble(ports portname,unsigned char value){
	value<<=4;
	switch(portname)
	{
		case DIO_PORTA:
			PORTA&=0x0f;
			PORTA|=value;
		break;
		case DIO_PORTB:
			PORTB&=0x0f;
			PORTB|=value;
		break;
		case DIO_PORTC:
			PORTC&=0x0f;
			PORTC|=value;
		break;
		case DIO_PORTD:
			PORTD&=0x0f;
			PORTD|=value;
		break;
	}
}
