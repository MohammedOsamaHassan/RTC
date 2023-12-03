/*
 * LCD.h
 *
 * Created: 11/3/2023 9:01:12 PM
 *  Author: M Osama
 */ 


#ifndef LCD_H_
#define LCD_H_

/******************** includes******************************/
#include "DIO.h"
#include "LCD_Config.h"

/********************* macros ******************************/
#define CLR_LCD							0x01
#define RETURN_HOME						0x02
#define ENTRY_MODE						0x06
#define DISPLAY_ON_CURSOR_ON			0x0E

#define LCD_PORT					DIO_PORTA
#define CONTROL_PORT				DIO_PORTA
#define RS							DIO_PIN0
#define RW							DIO_PIN1
#define EN							DIO_PIN2

#if LCD_MODE == eight_bit_mode
#define EIGHT_BITS                   0x38
#elif LCD_MODE == four_bit_mode
#define FOUR_BITS                    0x28
#endif

/************************APIs***********************/
void LCD_vInit(void);
static void send_falling_edge(void);
void LCD_vSend_cmd(char cmd);
void LCD_vSend_char(char data);
void LCD_vSend_string(char *data);
void LCD_clearscreen();
void LCD_movecursor(char row,char coloumn);
void LCD_vSend_int(int Number);
void LCD_vSend_float(float Number);


#endif /* LCD_H_ */