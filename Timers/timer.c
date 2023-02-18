/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.c
 *
 * Description: source file for the timer driver
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "common_macros.h"

/******************************************************************
 *                        Global Variables                        *
 ******************************************************************/

static void(*g_callBackPtr0)(void)=NULL_PTR;      /* Call back function of timer 0 */
static void(*g_callBackPtr1)(void)=NULL_PTR;      /* Call back function of timer 1 */
static void(*g_callBackPtr2)(void)=NULL_PTR;      /* Call back function of timer 2 */


volatile uint32 SECONDS_T1=0;
volatile uint32 SECONDS_T1_MC1=0;
volatile uint32 SECONDS_T1_MC2=0;
/*******************************************************************
 *                                  ISR                            *
 *******************************************************************/
//For timer 0 -> overflow (normal) mode
ISR(TIMER0_OVF_vect){
	if(g_callBackPtr0 != NULL_PTR)
	{
		(*g_callBackPtr0)();  /* Call call back function */
	}
}

ISR(TIMER0_COMP_vect){
	if(g_callBackPtr0 != NULL_PTR)
	{
		(*g_callBackPtr0)();  /* Call call back function */
	}
}

//For timer 1 -> overflow (normal) mode
ISR(TIMER1_OVF_vect){
	if(g_callBackPtr1 != NULL_PTR)
	{
		(*g_callBackPtr1)();  /* Call call back function */
	}
}

ISR(TIMER1_COMPA_vect){
	if(g_callBackPtr1 != NULL_PTR)
	{
		(*g_callBackPtr1)();  /* Call call back function */
	}
}

//For timer 2 -> overflow (normal) mode
ISR(TIMER2_OVF_vect){
	if(g_callBackPtr2 != NULL_PTR)
	{
		(*g_callBackPtr2)();  /* Call call back function */
	}
}

ISR(TIMER2_COMP_vect){
	if(g_callBackPtr2 != NULL_PTR)
	{
		(*g_callBackPtr2)();  /* Call call back function */
	}
}

/*******************************************************************************
 *                      Functions declaration                                   *
 *******************************************************************************/
/***************************************************
 * Description : Initialize the Timer
 * Argument    : pointer to struct (TIMER_congif)
 * Returns     : None
 ***************************************************/
void Timer_init(const TIMER_config * Config_Ptr){
	switch(Config_Ptr->channel){

	case timer0:
		SET_BIT(TCCR0,FOC0);//for non PWM mode
		if(Config_Ptr->mode==normal){
			//enable interrupt for normal mode -> timer 0
			SET_BIT(TIMSK,TOIE0);
			//Activate normal (overflow) mode
			CLEAR_BIT(TCCR0,WGM00);
			CLEAR_BIT(TCCR0,WGM01);
			//disconnect OC0
			CLEAR_BIT(TCCR0,COM00);
			CLEAR_BIT(TCCR0,COM01);
		}
		else if(Config_Ptr->mode==ctc){
			//enable interrupt for CTC mode -> timer 0
			SET_BIT(TIMSK,OCIE0);
			//Activate CTC (compare) mode
			CLEAR_BIT(TCCR0,WGM00);
			SET_BIT(TCCR0,WGM01);
			//add the compare value
			OCR0=(uint8)Config_Ptr->compare_value;
		}
		TCNT0 =0; /* Clear counter register */
		TCCR0 =(TCCR0 &(~0X07)) | (Config_Ptr->clock & 0x07); /* configure Pre-scaler */
		break;

	case timer1:
		//for non PWM mode
		SET_BIT(TCCR1A,FOC1A);
		SET_BIT(TCCR1A,FOC1B);
		if(Config_Ptr->mode==normal){
			//enable interrupt for normal mode -> timer 1
			SET_BIT(TIMSK,TOIE1);
			TCCR1B=0;
			TCCR1A &= ~0XF3;
		}
		else if(Config_Ptr->mode==ctc){
			//enable interrupt for CTC mode -> timer 1
			SET_BIT(TIMSK,OCIE1A);
			//activate compare mode
			TCCR1B |= 0X08; /* set bit WGM12 Bit 3*/
			TCCR1A &= ~0XF3;
			OCR1A = Config_Ptr->compare_value; /* enter compare value */
		}
		TCNT1=0;    /* Clear Counter 1 */
		TCCR1B =(TCCR1B &(~0X07)) | (Config_Ptr->clock & 0x07); /* configure Pre-scaler */
		break;

	case timer2:
		//for non PWM mode
		SET_BIT(TCCR2,FOC2);
		if(Config_Ptr->mode==normal){
			//enable interrupt for normal mode -> timer 2
			SET_BIT(TIMSK,OCIE2);
			TCCR2 &= ~0X78;
		}
		else if(Config_Ptr->mode==ctc){
			//enable interrupt for CTC mode -> timer 2
			SET_BIT(TIMSK,TOIE2);
			TCCR2 |= 0X08;        /* WGM20 0 WGM21 1 Normal CTC Mode */
			OCR2 =(uint8) Config_Ptr->compare_value; /* enter compare value*/
		}
		TCNT2 =0; /* Clear counter register */
		TCCR2 =(TCCR2 &(~0X07)) | (Config_Ptr->clock & 0x07); /* configure Pre-scaler */
		break;
	}
}

/***************************************************
 * Description : deinitialize the Timer
 * Argument    : channel of the timer -> timer 0,1,2
 * Returns     : None
 ***************************************************/

void Timer_deInit(Timer_channel channel){
	switch (channel)
	{
	case timer0:
		TIMSK &= ~0X03; /* Disable All TIMER0 interrupt */
		TCNT0=0;        /* Disable timer0 */
		TCCR0=0;        /* Clear Counter*/
		OCR0=0;         /*Clear Compare Register*/
		break;
	case timer1:
		TIMSK &= ~0X1C; /*Disable All TIMER1 Interrupt */
		TCCR1A=0;       /* Disable Timer1 */
		TCCR1B=0;
		TCNT1=0;        /* Clear Counter*/
		OCR1A=0;        /*Clear Compare Register*/

		break;
	case timer2:
		TIMSK &= ~0XC0; /* Disable All TIMER2 interrupt */
		TCNT2=0;        /* Disable TIMER2 */
		TCCR2=0;        /* Clear Counter*/
		OCR0=0;         /*Clear Compare Register*/
		break;
	}
}

/***************************************************
 * Description : Function to set the Call Back function address
 * Argument    : channel of the timer -> timer 0,1,2
 * 				 pointer to Call Back function
 * Returns     : None
 ***************************************************/

void Timer_setCallBack(Timer_channel channel,void(*a_ptr)(void)){
	switch(channel){
	case timer0:
		g_callBackPtr0=a_ptr;
		break;
	case timer1:
		g_callBackPtr1=a_ptr;
		break;
	case timer2:
		g_callBackPtr2=a_ptr;
		break;

	}
}


