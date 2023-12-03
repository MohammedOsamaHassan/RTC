/*
 * KEYPAD.h
 *
 * Created: 11/4/2023 8:22:38 PM
 *  Author: M Osama
 */ 


#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "DIO.h"
#define NOTPRESSED 0xFF
#define KEYPAD_PORT  DIO_PORTD

void keypad_vInit();
char keypad_u8check_press();






#endif /* KEYPAD_H_ */