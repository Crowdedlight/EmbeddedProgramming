/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: task_rtc.h
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

#ifndef _TASK_RTC_H
  #define _TASK_RTC_H

/***************************** Include files *******************************/
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "emp_type.h"
#include "time_functions.h"
#include "events.h"
#include "messages.h"
#include "tmodel.h"
#include "swtimers.h"
/*****************************    Defines    *******************************/
#define RTCST_INIT	0
#define RTCST_RUN	1
/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void task_rtc( INT8U task_num );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Task for our real time clock
******************************************************************************/

/****************************** End Of Module *******************************/
#endif

