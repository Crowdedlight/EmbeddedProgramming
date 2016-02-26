/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: task_lcd.h
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

#ifndef _TASK_LCD_H
  #define _TASK_LCD_H

/***************************** Include files *******************************/
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "emp_type.h"
#include "events.h"
#include "tmodel.h"
#include "messages.h"
#include "swtimers.h"
#include "lcd.h"
/*****************************    Defines    *******************************/
#define LCD_INIT	0
#define LCD_RUNNING 1
#define LCD_PAUSED  2

//LCD positions
#define POS_HH  5
#define POS_MM  8
#define POS_COL 7
#define POS_LINE 1

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void task_lcd ( INT8U TASK_NUM );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Task for our LCD
******************************************************************************/

void lcd_toggle_col();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Function to make Colon blink
******************************************************************************/

void lcd_update();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Function to update time
******************************************************************************/

/****************************** End Of Module *******************************/
#endif

