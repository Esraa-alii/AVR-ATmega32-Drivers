/******************************************************************************
 *
 * Module: Buzzer
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer driver
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_
#include "std_types.h"


/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define BUZZER_portID           PORTD_ID
#define BUZZER_positive_PinID   PIN6_ID
#define BUZZER_negative_PinID   PIN7_ID

/*******************************************************************************
 *                              Functions Prototypes                           *
 *******************************************************************************/

/***************************************************
 * Description : Initialize the buzzer to be off
 * Argument    : None
 * Returns     : None
 ***************************************************/
void Buzzer_init(void);

/***************************************************
 * Description : Turn on the buzzer
 * Argument    : None
 * Returns     : None
 ***************************************************/
void Buzzer_on(void);

/***************************************************
 * Description : Turn off the buzzer
 * Argument    : None
 * Returns     : None
 ***************************************************/
void Buzzer_off(void);


#endif
