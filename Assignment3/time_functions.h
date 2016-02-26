/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: time_functions.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: Change time.
*
******************************************************************************/

#ifndef TIME_FUNCTIONS_H_
#define TIME_FUNCTIONS_H_

/***************************** Include files *******************************/
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "emp_type.h"
#include "swtimers.h"
#include "tmodel.h"
#include "messages.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

INT8U time_incr(void);
/*****************************************************************************
*   Input    : Button Event
*   Output   : Update state buffer
*   Function : Increment min. and reset seconds
******************************************************************************/

INT8U time_decr(void);
/*****************************************************************************
*   Input    : Button Event
*   Output   : Update state buffer
*   Function : Decrement min. and reset seconds
******************************************************************************/


/****************************** End Of Module *******************************/
#endif /*TIME_FUNCTIONS_H_*/




