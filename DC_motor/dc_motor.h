/******************************************************************************
 *
 * Module: DC motor
 *
 * File Name: dc_motor.h
 *
 * Description: Header file for the DC motor driver
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/

#ifndef DC_MOTOR_H_
#define DC_MOTOR_H_

#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
typedef enum{
	DC_Motor_stop,DC_Motor_clockwise,DC_Motor_Anticlockwise
}DC_Motor_state;


/***************************************************
 * Description : Initialize the direction of Motor
 * Argument    : None
 * Returns     : None
 ***************************************************/
void DcMotor_Init(void);

/***************************************************
 * Description : -The function responsible for rotate the DC Motor CW/ or A-CW or
				 stop the motor based on the state input state value.
				 -Send the required duty cycle to the PWM driver based on the
				 required speed value
 * Argument    : Dc_motor_state -> stop/clockwise/anti clockwise
 * 			    speed -> duty cycle
 * Returns      : No Return Type
 ***************************************************/
void DcMotor_Rotate(DC_Motor_state state,uint8 speed);

#endif
