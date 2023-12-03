/*
 * DIO.h
 *
 * Created: 10/2/2023 8:46:45 PM
 *  Author: M Osama
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "BIT_Math.h"

typedef enum {
	DIO_PORTA = 0,
	DIO_PORTB,
	DIO_PORTC,
	DIO_PORTD
}ports;

typedef enum {
	DIO_PIN0 = 0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
}pins;

typedef enum {
	DIO_INPUT = 0,
	DIO_OUTPUT
}directions;

typedef enum {
	PULLUP_NO_CONNECT = 0,
	PULLUP_CONNECT	
	
}connection;


/*APIs*/
/*pins*/
void DIO_pin_dierction (ports port ,pins pin ,directions direction);
void DIO_pin_write (ports port ,pins pin ,unsigned char val);
unsigned char DIO_pin_read (ports port ,pins pin );
void DIO_pin_toggle (ports port ,pins pin );
void DIO_connectPullUP(ports port ,pins pin, connection connect);
/*ports*/
void DIO_port_dierction (ports port ,unsigned char direction);
void DIO_port_write (ports port ,unsigned char val);
unsigned char DIO_port_read (ports port);
void DIO_port_toggle (ports port );

void write_low_nibble(ports portname,unsigned char value);
void write_high_nibble(ports portname,unsigned char value);



#endif /* DIO_H_ */