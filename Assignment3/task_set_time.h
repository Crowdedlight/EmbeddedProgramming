/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: task_set_time.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION:
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 160226  SSJ	Module created.
*
*****************************************************************************/

#ifndef _TASK_SET_TIME_H
  #define _TASK_SET_TIME_H

/***************************** Include files *******************************/
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "emp_type.h"
#include "time_functions.h"
#include "task_button.h"
#include "events.h"
#include "messages.h"
#include "tmodel.h"
/*****************************    Defines    *******************************/
#define STST_IDLE	0
#define STST_INCR	1
#define STST_DECR 	2
/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
void task_set_time( INT8U task_num );
/*****************************************************************************
*   Input    : Task handle.
*   Output   : -
*   Function : Sets time.
******************************************************************************/


/****************************** End Of Module *******************************/
#endif

