/*
 * Timer2.c
 *
 * Created: 12/2/2023 5:17:43 AM
 *  Author: M Osama
 */ 

#include "Timer2.h"

void Timer2_OVF_init_interrupt(void){
	/*Select OVF mode*/
	CLR_BIT(TCCR2,WGM20);
	CLR_BIT(TCCR2,WGM21);
	/*Select clock on pin TOSC1*/
	SET_BIT(ASSR,AS2);
	/*Select 128 Prescaler*/
	SET_BIT(TCCR2,CS20);
	CLR_BIT(TCCR2,CS21);
	SET_BIT(TCCR2,CS22);
	/*enable interrupt*/
	sei();
	SET_BIT(TIMSK, TOIE2);	
}
