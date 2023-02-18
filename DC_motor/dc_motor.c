/******************************************************************************
 *
 * Module: DC motor
 *
 * File Name: lcd.c
 *
 * Description: Source file for the DC motor driver
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/

#include "dc_motor.h" /* header file of DC motor*/
#include "common_macros.h"
#include "gpio.h" /* header file of GPIO*/
#include "avr/io.h" /* To use the DC motor register*/
#include "pwm.h" /* header file of PWM*/
/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/***************************************************
 * Description : Initialize the direction of Motor
 * Argument    : None
 * Returns     : None
 ***************************************************/

void DcMotor_Init(void){
	GPIO_setupPinDirection(PORTB_ID,PIN0_ID,PIN_OUTPUT); /* set PB0 as Output PIN */
	GPIO_setupPinDirection(PORTB_ID,PIN1_ID,PIN_OUTPUT); /* set PB1 as Output PIN*/
	//initialize the motor to be stopped
	GPIO_writePin(PORTB_ID,PIN0_ID,LOGIC_LOW);
	GPIO_writePin(PORTB_ID,PIN1_ID,LOGIC_LOW);
}
/***************************************************
 * Description : -The function responsible for rotate the DC Motor CW/ or A-CW or
				 stop the motor based on the state input state value.
				 -Send the required duty cycle to the PWM driver based on the
				 required speed value
 * Argument    : Dcmotor state -> stop/clockwise/anti clockwise
 * 			    speed -> duty cycle
 * Returns      : No Return Type
 ***************************************************/
void DcMotor_Rotate(DC_Motor_state state,uint8 speed){
	PORTB = (PORTB & 0xFC) | (state & 0x03); // Set Direction of DCMotor (CW / A-CW / Stop) based on state argument //
	PWM_Timer0_Start(speed); // Set Duty cycle to PWM Driver Based on Speed Argument //

}

