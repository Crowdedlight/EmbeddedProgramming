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
* 160226  FMA	Renamed Module
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "task_rtc.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/


void task_rtc( INT8U task_num )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Task for our real time clock
******************************************************************************/
{
	static INT8U rtc_state = RTCST_INIT;
	INT8U sec;
	INT8U min;
	INT8U hour;

	switch( rtc_state )
	{
	case RTCST_INIT:
		sec = 0;
		min = 0;
		hour = 0;
		put_msg_state( SSM_CLOCK_SEC, sec );
		put_msg_state( SSM_CLOCK_MIN, min );
		put_msg_state( SSM_CLOCK_HOUR, hour );
		start_swtimer( ST_CLOCK, SEB_CLOCK_EVENT, MILLISEC(1000) );
		rtc_state = RTCST_RUN;
		break;
	case RTCST_RUN:
		if( get_msg_event( SEB_CLOCK_EVENT ) )
		{
			sec = get_msg_state( SSM_CLOCK_SEC );
			if( ++sec == 60 )
			{
				time_incr();		// Increments min and sets sec = 0
				put_msg_event( SEB_LCD_EVENT, LCDE_UPDATE );
				sec = 0;
			}
			put_msg_state( SSM_CLOCK_SEC,sec );
			start_swtimer( ST_CLOCK, SEB_CLOCK_EVENT, MILLISEC(1000) );
		}
		break;
	default:
		break;
	}

}

/****************************** End Of Module *******************************/

