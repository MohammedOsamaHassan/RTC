/*
 * LCD.c
 *
 * Created: 11/3/2023 9:00:58 PM
 *  Author: M Osama
 */ 

#include "LCD.h"
#define F_CPU 8000000UL
#include <util/delay.h>

void LCD_vInit(void){
	_delay_ms(200);
	#if LCD_MODE == eight_bit_mode
	unsigned char counter = 0;
	/* initialize pin directions */
	for (counter = 0 ; counter < 8 ; counter++)
	{
		DIO_pin_dierction(LCD_PORT,counter,DIO_OUTPUT);
	}
	DIO_pin_dierction(CONTROL_PORT,RS,DIO_OUTPUT);
	DIO_pin_dierction(CONTROL_PORT,RW,DIO_OUTPUT);
	DIO_pin_dierction(CONTROL_PORT,EN,DIO_OUTPUT);
	
	DIO_pin_write(CONTROL_PORT,RW,0);
	
	/* send commands */
	
	LCD_vSend_cmd(EIGHT_BITS); // 8bit Mode
	_delay_ms(1);
	LCD_vSend_cmd(DISPLAY_ON_CURSOR_ON); // display on cursor on
	_delay_ms(1);
	LCD_clearscreen(); // clear display
	LCD_vSend_cmd(ENTRY_MODE);// display on cursor on
	_delay_ms(1);

	#elif LCD_MODE == four_bit_mode
	unsigned char counter = 0;
	/* initialize pin directions */
	for (counter = 4 ; counter < 8 ; counter++)
	{
		DIO_pin_dierction(LCD_PORT,counter,DIO_OUTPUT);
	}
	DIO_pin_dierction(CONTROL_PORT,RS,DIO_OUTPUT);
	DIO_pin_dierction(CONTROL_PORT,RW,DIO_OUTPUT);
	DIO_pin_dierction(CONTROL_PORT,EN,DIO_OUTPUT);
	
	DIO_pin_write(CONTROL_PORT,RW,0);
	
	/* send commands */
	LCD_vSend_cmd(RETURN_HOME); // return cursor home
	_delay_ms(10);
	LCD_vSend_cmd(FOUR_BITS); // 8bit Mode
	_delay_ms(1);
	LCD_vSend_cmd(DISPLAY_ON_CURSOR_ON); // display on cursor on
	_delay_ms(1);
	LCD_clearscreen(); // clear display
	LCD_vSend_cmd(ENTRY_MODE);// display on cursor on
	_delay_ms(1);
	#endif	
	
}

static void send_falling_edge(void){
	DIO_pin_write(CONTROL_PORT,EN,1);
	_delay_ms(2);
	DIO_pin_write(CONTROL_PORT,EN,0);
	_delay_ms(2);
	
}

void LCD_vSend_cmd(char cmd){
	#if LCD_MODE == eight_bit_mode
	DIO_port_write(LCD_PORT,cmd);
	DIO_pin_write(CONTROL_PORT,RS,0);
	send_falling_edge();
	#elif LCD_MODE == four_bit_mode
	write_high_nibble(LCD_PORT,cmd>>4);
	DIO_pin_write(CONTROL_PORT,RS,0);
	send_falling_edge();
	write_high_nibble(LCD_PORT,cmd);
	DIO_pin_write(CONTROL_PORT,RS,0);
	send_falling_edge();
	#endif
	_delay_ms(1);		
	
}
void LCD_vSend_char(char data){
	#if LCD_MODE == eight_bit_mode
	DIO_port_write(LCD_PORT,data);
	DIO_pin_write(CONTROL_PORT,RS,1);
	send_falling_edge();
	#elif LCD_MODE == four_bit_mode
	write_high_nibble(LCD_PORT,data>>4);
	DIO_pin_write(CONTROL_PORT,RS,1);
	send_falling_edge();
	write_high_nibble(LCD_PORT,data);
	DIO_pin_write(CONTROL_PORT,RS,1);
	send_falling_edge();
	#endif	
	_delay_ms(1);
	
}
void LCD_vSend_string(char *data){
	while ( (*data) != '\0'){
		LCD_vSend_char(*data);
		data++;
	}		
	
}

void LCD_clearscreen(){
	LCD_vSend_cmd(CLR_LCD);
	_delay_ms(10);	
	
}

void LCD_movecursor(char row,char coloumn){
	unsigned char position = 0;
	if (row > 2 || row < 1 || coloumn > 16 || coloumn < 1)
	{
		position = 0x80;
	}	
	else if (row == 1){
		position = 0x80 + coloumn - 1;
	}
	else if (row == 2){
		position = 0xC0 + coloumn - 1;
	}
	LCD_vSend_cmd(position);
	_delay_ms(1);
}

void LCD_vSend_int(int Number){
	if (Number < 10)
	{
		LCD_vSend_char(Number + 48);
	}
	else if (Number < 100)
	{
		LCD_vSend_char((Number/10) + 48);
		LCD_vSend_char((Number%10) + 48);
	}
	else if (Number < 1000)
	{
		LCD_vSend_char((Number/100) + 48);
		Number %= 100;
		LCD_vSend_char((Number/10) + 48);
		LCD_vSend_char((Number%10) + 48);
	}
	else if (Number < 10000)
	{
		LCD_vSend_char((Number/1000) + 48);
		Number %= 1000;
		LCD_vSend_char((Number/100) + 48);
		Number %= 100;
		LCD_vSend_char((Number/10) + 48);
		LCD_vSend_char((Number%10) + 48);
	}
	else if (Number < 100000)
	{
		LCD_vSend_char((Number/10000) + 48);
		Number %= 10000;
		LCD_vSend_char((Number/1000) + 48);
		Number %= 1000;
		LCD_vSend_char((Number/100) + 48);
		Number %= 100;
		LCD_vSend_char((Number/10) + 48);
		LCD_vSend_char((Number%10) + 48);
	}
	else{}

}


void LCD_vSend_float(float Number){
	int INumber = 0;
	int FNumber = 0;
	
	INumber = (int)Number;
	Number = Number - INumber;
	FNumber = (int)(Number*1000);
	if (FNumber != 0)
	{
		while ((FNumber%10) == 0)
		{
			FNumber /= 10;
		}
		LCD_vSend_int(INumber);
		LCD_vSend_char('.');
		LCD_vSend_int(FNumber);
	}
	else
	{
		LCD_vSend_int(INumber);	
	}
	
		
}
