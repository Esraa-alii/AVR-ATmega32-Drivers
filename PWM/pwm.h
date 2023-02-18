/******************************************************************************
 *
 * Module: Pwm
 *
 * File Name: pwm.h
 *
 * Description: Header file for the LCD driver
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/

#ifndef PWM_H_
#define PWM_H_
#include "std_types.h"
/**********************************************************
 *                Functions Prototypes                     *
 **********************************************************/


/****************************************************
 * Function Name : PWM_Timer0_Start
 * Description   : 1- Setup the PWM mode with Non-Inverting.
 *                2- Setup the pre-scaler with F_CPU/8
 *                3- Setup the compare value based on the required input duty cycle
 *                4- Setup the direction for OC0 as output pin through the GPIO driver.
 *                5- The generated PWM signal frequency will be 500Hz to control the DC Motor speed.
 * Arguments     : duty cycle passed by DCMotor Driver
 * Returns       : No Return Type
 ****************************************************/
void PWM_Timer0_Start(uint8 duty_cycle);


#endif /* PWM_H_ */
