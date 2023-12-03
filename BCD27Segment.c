/*
 * BCD27Segment.c
 *
 * Created: 10/15/2023 7:19:16 PM
 *  Author: M Osama
 */ 

#include "BCD27Segment.h"

void seven_seg_init (ports port){
	DIO_pin_dierction(port,DIO_PIN4,DIO_OUTPUT);
	DIO_pin_dierction(port,DIO_PIN5,DIO_OUTPUT);
	DIO_pin_dierction(port,DIO_PIN6,DIO_OUTPUT);
	DIO_pin_dierction(port,DIO_PIN7,DIO_OUTPUT);
}
void seven_seg_write (ports port, unsigned char val){
	write_high_nibble(port,val);		
}