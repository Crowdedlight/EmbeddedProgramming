/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: main.c
*
* PROJECT....: EMP
*
* DESCRIPTION: Assignment 3, main module. No main.h file.
*
******************************************************************************/

/***************************** Include files *******************************/
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "emp_type.h"
#include "systick.h"
#include "gpio.h"
#include "swtimers.h"
#include "task_rtc.h"
#include "task_button.h"
#include "task_lcd.h"
#include "task_set_time.h"


/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/
extern volatile INT16S ticks;
INT16S alive_timer = MILLISEC(500);

/*****************************   Functions   *******************************/


int main(void)
/*****************************************************************************
*   Input    :
*   Output   :
*   Function : The super loop.
******************************************************************************/
{
  INT8U event;
  INT8U counter_value;

  disable_global_int();
  init_systick();
  init_gpio();
  enable_global_int();


  // Loop forever.
  while(1)
  {
	// System part of the super loop.
	// ------------------------------
	while( !ticks );


	// The following will be executed every 5mS
	ticks--;

	if( ! --alive_timer )
	{
    	alive_timer =	MILLISEC( 500 );
	  	GPIO_PORTD_DATA_R ^= 0x40;
	}

    // Protected operating system mode
    swt_ctrl();

    // Application mode
    task_rtc( TASK_RTC );
    task_button( TASK_BUTTON );
    task_set_time( TASK_SET_TIME );
    task_lcd( TASK_LCD );
  }
}

/****************************** End Of Module *******************************/


