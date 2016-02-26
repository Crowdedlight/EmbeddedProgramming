/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: time_functions.c
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: Change time.
*
******************************************************************************/

/***************************** Include files *******************************/
#include "time_functions.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

INT8U time_incr(void)
/*****************************************************************************
*   Input    : Button Event
*   Output   : Update state buffer
*   Function : Increment min. and reset seconds
******************************************************************************/
{
	INT8U sec;
	INT8U min;
	INT8U hour;

	sec = 0;
	min = get_msg_state( SSM_CLOCK_MIN );

	if( ++min == 60 )
	{
		min = 0;
		hour = get_msg_state( SSM_CLOCK_HOUR );
		if( ++hour == 24 )
		{
			hour = 0;
		}
		put_msg_state( SSM_CLOCK_HOUR,hour );
	}
	put_msg_state( SSM_CLOCK_MIN,min );
	put_msg_state( SSM_CLOCK_SEC,sec );
}

INT8U time_decr(void)
/*****************************************************************************
*   Input    : Button Event
*   Output   : Update state buffer
*   Function : Decrement min. and reset seconds
******************************************************************************/
{

	INT8U sec;
	INT8U min;
	INT8U hour;

	sec = 0;
	min = get_msg_state( SSM_CLOCK_MIN );

	if( min-- == 0 )
	{
		min = 59;
		hour = get_msg_state( SSM_CLOCK_HOUR );
		if( hour-- == 0 )
		{
			hour = 23;
		}
		put_msg_state( SSM_CLOCK_HOUR,hour );
	}

	put_msg_state( SSM_CLOCK_MIN,min );
	put_msg_state( SSM_CLOCK_SEC,sec );
}


/****************************** End Of Module *******************************/
