/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: button.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090215  MoH   Module created.
*
*****************************************************************************/

#ifndef TASK_BUTTON_H_
#define TASK_BUTTON_H_

/***************************** Include files *******************************/
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "emp_type.h"
#include "events.h"
#include "swtimers.h"
#include "tmodel.h"
#include "messages.h"

/*****************************    Defines    *******************************/
#define BS_IDLE           0
#define BS_FIRST_PUSH     1
#define BS_FIRST_RELEASE  2
#define BS_SECOND_PUSH    3
#define BS_LONG_PUSH      4

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

INT8U select_button(void);

/*****************************************************************************
*   Input    : -
*   Output   : Button Event
*   Function : Test function
******************************************************************************/


/****************************** End Of Module *******************************/
#endif /*BUTTON_H_*/
