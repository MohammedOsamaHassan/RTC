/*
 * RTC.c
 *
 * Created: 12/2/2023 4:46:42 AM
 *  Author: M Osama
 */ 

#define F_CPU     8000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "BCD27Segment.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "Timer2.h"
#include "LCD.h"

void Interrupt_int(void);
void SetClockMode(void);
void AlarmMode(void);

volatile unsigned char Second_counter = 0;
unsigned char minutes_counter = 0;
unsigned char hours_counter = 0;
unsigned char SetHours = 0;
unsigned char SetMinuts = 0;
unsigned char SetSeconds = 0;
unsigned char AlarmHours = 0;
unsigned char AlarmMinuts = 0;
volatile unsigned char CloseFlag = 0;

unsigned char SetButton = NOTPRESSED;
unsigned char mode = NOTPRESSED;

int main(void)
{
	LED_vInit(DIO_PORTB,DIO_PIN1);
	Interrupt_int();
	LCD_vInit();
	keypad_vInit();
	seven_seg_init(DIO_PORTB);
	DIO_pin_dierction(DIO_PORTB,DIO_PIN0,DIO_OUTPUT);
	DIO_pin_dierction(DIO_PORTC,DIO_PIN0,DIO_OUTPUT);
	DIO_pin_dierction(DIO_PORTC,DIO_PIN1,DIO_OUTPUT);
	DIO_pin_dierction(DIO_PORTC,DIO_PIN2,DIO_OUTPUT);
	DIO_pin_dierction(DIO_PORTC,DIO_PIN3,DIO_OUTPUT);
	DIO_pin_dierction(DIO_PORTC,DIO_PIN4,DIO_OUTPUT);
	DIO_pin_dierction(DIO_PORTC,DIO_PIN5,DIO_OUTPUT);
	
	DIO_pin_dierction(DIO_PORTB,DIO_PIN2,DIO_INPUT);
	DIO_connectPullUP(DIO_PORTB,DIO_PIN2,PULLUP_CONNECT);
	
	Timer2_OVF_init_interrupt();
	
	label:
	LCD_clearscreen();
	LCD_vSend_string("1: Set Clock");
	LCD_movecursor(2,1);
	LCD_vSend_string("2: Alarm");
    while(1)
    {
		mode = keypad_u8check_press();
		if (mode != NOTPRESSED)
		{
			if (mode == '1')
			{
				mode = NOTPRESSED;
				SetClockMode();
				goto label;
			}
			else if(mode == '2')
			{
				mode = NOTPRESSED;
				AlarmMode();
				goto label;
			}
			else
			{
				LCD_clearscreen();
				LCD_vSend_string("Wrong choice");
				_delay_ms(1000);
				goto label;
			}
		}
		else{}
		
		
		/*Seven Segment Display*/
		DIO_pin_write(DIO_PORTC,DIO_PIN0,0);
		DIO_pin_write(DIO_PORTC,DIO_PIN1,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN2,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN3,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN4,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN5,1);
		seven_seg_write(DIO_PORTB,Second_counter%10);
		_delay_ms(5);
		
		DIO_pin_write(DIO_PORTC,DIO_PIN0,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN1,0);
		DIO_pin_write(DIO_PORTC,DIO_PIN2,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN3,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN4,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN5,1);
		seven_seg_write(DIO_PORTB,Second_counter/10);
		_delay_ms(5);
		
		DIO_pin_write(DIO_PORTC,DIO_PIN0,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN1,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN2,0);
		DIO_pin_write(DIO_PORTC,DIO_PIN3,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN4,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN5,1);
		seven_seg_write(DIO_PORTB,minutes_counter%10);
		_delay_ms(5);
		
		DIO_pin_write(DIO_PORTC,DIO_PIN0,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN1,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN2,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN3,0);
		DIO_pin_write(DIO_PORTC,DIO_PIN4,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN5,1);
		seven_seg_write(DIO_PORTB,minutes_counter/10);
		_delay_ms(5);
		
		DIO_pin_write(DIO_PORTC,DIO_PIN0,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN1,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN2,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN3,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN4,0);
		DIO_pin_write(DIO_PORTC,DIO_PIN5,1);
		seven_seg_write(DIO_PORTB,hours_counter%10);
		_delay_ms(5);
		
		DIO_pin_write(DIO_PORTC,DIO_PIN0,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN1,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN2,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN3,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN4,1);
		DIO_pin_write(DIO_PORTC,DIO_PIN5,0);
		seven_seg_write(DIO_PORTB,hours_counter/10);
		_delay_ms(5);
		
		
		if(Second_counter == 60)
		{
			Second_counter = 0;
			minutes_counter++;
		}
		else{}
			
		if (minutes_counter == 60)
		{
			minutes_counter = 0;
			hours_counter++;
		}
		else{}
			
		if (hours_counter == 24)
		{
			hours_counter = 0;
		}
		else{}
			
		if (hours_counter == AlarmHours && minutes_counter == AlarmMinuts && hours_counter != 0 && minutes_counter != 0 && CloseFlag == 0)
		{
			DIO_pin_write(DIO_PORTB,DIO_PIN0,1);
		}
		else
		{
			DIO_pin_write(DIO_PORTB,DIO_PIN0,0);
		}
		
    }
}

void Interrupt_int(void){
	sei();
	CLR_BIT(MCUCSR,ISC2);
	SET_BIT(GICR,INT2);	
}

void SetClockMode(void){
	unsigned char CorrectHoursFlag = 0;
	unsigned char CorrectMinutesFlag = 0;
	unsigned char CorrectSecondsFlag = 0;
	
	/*Set hours*/
	while (CorrectHoursFlag == 0)
	{	
		LCD_clearscreen();
		LCD_vSend_string("Set Hours :");
		do
		{
			SetButton = keypad_u8check_press();
		} while (SetButton == NOTPRESSED);
		LCD_vSend_char(SetButton);
		SetHours = SetButton - 48;
		SetButton = NOTPRESSED;
		do
		{
			SetButton = keypad_u8check_press();
		} while (SetButton == NOTPRESSED);
		LCD_vSend_char(SetButton);
		SetHours = (SetHours*10) + (SetButton-48);
		_delay_ms(300);
		
		if (SetHours > 24 )
		{
			CorrectHoursFlag = 0;
			LCD_clearscreen();
			LCD_vSend_string("Out of range");
			_delay_ms(1000);
		}
		else
		{
			CorrectHoursFlag = 1;
		}
	}
	
	/*Set minuets*/
	while (CorrectMinutesFlag == 0)
	{
		LCD_clearscreen();
		LCD_vSend_string("Set Minuets :");
		do
		{
			SetButton = keypad_u8check_press();
		} while (SetButton == NOTPRESSED);
		LCD_vSend_char(SetButton);
		SetMinuts = SetButton - 48;
		SetButton = NOTPRESSED;
		do
		{
			SetButton = keypad_u8check_press();
		} while (SetButton == NOTPRESSED);
		LCD_vSend_char(SetButton);
		SetMinuts = (SetMinuts*10) + (SetButton-48);
		_delay_ms(300);

		if (SetMinuts > 60 )
		{
			CorrectMinutesFlag = 0;
			LCD_clearscreen();
			LCD_vSend_string("Out of range");
			_delay_ms(1000);
		}
		else
		{
			CorrectMinutesFlag = 1;
		}
	}
	
	/*Set seconds*/
	while (CorrectSecondsFlag == 0)
	{
		LCD_clearscreen();
		LCD_vSend_string("Set Seconds :");
		do
		{
			SetButton = keypad_u8check_press();
		} while (SetButton == NOTPRESSED);
		LCD_vSend_char(SetButton);
		SetSeconds = SetButton - 48;
		SetButton = NOTPRESSED;
		do
		{
			SetButton = keypad_u8check_press();
		} while (SetButton == NOTPRESSED);
		LCD_vSend_char(SetButton);
		SetSeconds = (SetSeconds*10) + (SetButton-48);
		_delay_ms(300);


		if (SetSeconds > 60 )
		{
			CorrectSecondsFlag = 0;
			LCD_clearscreen();
			LCD_vSend_string("Out of range");
			_delay_ms(1000);
		}
		else
		{
			CorrectSecondsFlag = 1;
		}	
	}
	
	Second_counter = SetSeconds;
	minutes_counter = SetMinuts;
	hours_counter = SetHours;	
	
	
}
void AlarmMode(void){
	unsigned char CorrectHoursFlag = 0;
	unsigned char CorrectMinutesFlag = 0;
	unsigned char CorrectSecondsFlag = 0;
	
	/*Rest Closeflag*/
	CloseFlag = 0;
	/*Select hours*/
	while (CorrectHoursFlag == 0)
	{
		LCD_clearscreen();
		LCD_vSend_string("Set Hours :");
		do
		{
			SetButton = keypad_u8check_press();
		} while (SetButton == NOTPRESSED);
		LCD_vSend_char(SetButton);
		AlarmHours = SetButton - 48;
		SetButton = NOTPRESSED;
		do
		{
			SetButton = keypad_u8check_press();
		} while (SetButton == NOTPRESSED);
		LCD_vSend_char(SetButton);
		AlarmHours = (AlarmHours*10) + (SetButton-48);
		_delay_ms(300);
		
		if (AlarmHours > 24 )
		{
			CorrectHoursFlag = 0;
			LCD_clearscreen();
			LCD_vSend_string("Out of range");
			_delay_ms(1000);
		}
		else
		{
			CorrectHoursFlag = 1;
		}
	}
	
	/*Set minuets*/
	while (CorrectMinutesFlag == 0)
	{
		LCD_clearscreen();
		LCD_vSend_string("Set Minuets :");
		do
		{
			SetButton = keypad_u8check_press();
		} while (SetButton == NOTPRESSED);
		LCD_vSend_char(SetButton);
		AlarmMinuts = SetButton - 48;
		SetButton = NOTPRESSED;
		do
		{
			SetButton = keypad_u8check_press();
		} while (SetButton == NOTPRESSED);
		LCD_vSend_char(SetButton);
		AlarmMinuts = (AlarmMinuts*10) + (SetButton-48);
		_delay_ms(300);

		if (SetMinuts > 60 )
		{
			CorrectMinutesFlag = 0;
			LCD_clearscreen();
			LCD_vSend_string("Out of range");
			_delay_ms(1000);
		}
		else
		{
			CorrectMinutesFlag = 1;
		}
	}
}

ISR (TIMER2_OVF_vect){
	Second_counter++;
}

ISR (INT2_vect){
	CloseFlag = 1;	
}










