/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.c
 *
 * Description: source file for the buzzer driver
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/

#include "buzzer.h"
#include "gpio.h"

/***************************************************
 * Description : Initialize the buzzer to be off
 * Argument    : None
 * Returns     : None
 ***************************************************/
void Buzzer_init(void){
	/* first set the 2 pin of the buzzer to be output
	 * then connect them to login low (GND) to be off */
	GPIO_setupPinDirection(BUZZER_portID,BUZZER_positive_PinID,PIN_OUTPUT);
	GPIO_setupPinDirection(BUZZER_portID,BUZZER_negative_PinID,PIN_OUTPUT);

	GPIO_writePin(BUZZER_portID,BUZZER_positive_PinID,LOGIC_LOW);
	GPIO_writePin(BUZZER_portID,BUZZER_negative_PinID,LOGIC_LOW);
}

/***************************************************
 * Description : Turn on the buzzer
 * Argument    : None
 * Returns     : None
 ***************************************************/
void Buzzer_on(void){
	/* connect the positive terminal to +ve and the negative terminal to ground */
	GPIO_writePin(BUZZER_portID,BUZZER_positive_PinID,LOGIC_HIGH);
	GPIO_writePin(BUZZER_portID,BUZZER_negative_PinID,LOGIC_LOW);
}

/***************************************************
 * Description : Turn on the buzzer
 * Argument    : None
 * Returns     : None
 ***************************************************/
void Buzzer_off(void){
	/* connect the positive terminal to -ve and the negative terminal to ground
	 * (open circuit) */
	GPIO_writePin(BUZZER_portID,BUZZER_positive_PinID,LOGIC_LOW);
	GPIO_writePin(BUZZER_portID,BUZZER_negative_PinID,LOGIC_LOW);
}
