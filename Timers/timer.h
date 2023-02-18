/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: timer.h
 *
 * Description: Header file for the timer driver
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

#include "std_types.h"

extern volatile uint32 SECONDS_T1;
extern volatile uint32 SECONDS_T1_MC1;
extern volatile uint32 SECONDS_T1_MC2;
/*******************************************************************************
                               Types Declaration
 *******************************************************************************/
typedef enum{
	timer0,timer1,timer2
}Timer_channel;

typedef enum {
	t_noClock,t_noPrescaling,t_clk8,t_clk64,t_clk256,t_clk1024,external_falling,external_rising,
	t2_noclock=0,t2_noPrescaling,t2_clk8,t2_clk32,t2_clk64,t2_clk128,t2_clk256,t2_clk1024
}Timer_clock;

typedef enum{
	normal,pwm,ctc,fast_pwm
}Timer_mode;

typedef struct{
	Timer_channel channel;
	Timer_clock clock;
	Timer_mode mode;
	uint16 compare_value;
}TIMER_config;


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/***************************************************
 * Description : Initialize the Timer
 * Argument    : pointer to struct (TIMER_congif)
 * Returns     : None
 ***************************************************/
void Timer_init(const TIMER_config * Config_Ptr);

/***************************************************
 * Description : deinitialize the Timer
 * Argument    : channel of the timer -> timer 0,1,2
 * Returns     : None
 ***************************************************/

void Timer_deInit(Timer_channel channel);

/***************************************************
 * Description : Function to set the Call Back function address
 * Argument    : channel of the timer -> timer 0,1,2
 * 				 pointer to Call Back function
 * Returns     : None
 ***************************************************/

void Timer_setCallBack(Timer_channel channel,void(*a_ptr)(void));

#endif
