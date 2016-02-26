/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: task_set_time.c
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

/***************************** Include files *******************************/
#include "task_set_time.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
void task_set_time( INT8U task_num )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Sets time.
******************************************************************************/
{
	static INT8U set_time_state = STST_IDLE;
	INT8U event = get_msg_event( SEB_BUTTON_EVENT );

	switch( set_time_state )
	{
		case STST_IDLE:		// Idle state
			switch( event )
			{
				case BE_LONG_PUSH:
					//Access / return from 'edit-time-mode'
					set_time_state = STST_INCR;
					put_msg_event( SEB_LCD_EVENT, LCDE_STOP );
			        break;
				default:
					break;
			}
			break;
		case STST_INCR:
			switch( event )
			{
				case BE_LONG_PUSH:
					set_time_state = STST_IDLE;
					put_msg_event( SEB_LCD_EVENT, LCDE_START );
					break;
				case BE_DOUBBLE_PUSH:
					set_time_state = STST_DECR;
					break;
				case BE_SINGLE_PUSH:
					time_incr();
					put_msg_event( SEB_LCD_EVENT, LCDE_UPDATE );
					break;
				default:
					break;
			}
			break;
		case STST_DECR:
			switch( event )
			{
				case BE_LONG_PUSH:
					set_time_state = STST_IDLE;
					put_msg_event( SEB_LCD_EVENT, LCDE_START );
					break;
				case BE_DOUBBLE_PUSH:
					set_time_state = STST_INCR;
					break;
				case BE_SINGLE_PUSH:
					time_decr();
					put_msg_event( SEB_LCD_EVENT, LCDE_UPDATE );
					break;
				default:
					break;
				}
			break;
		default:
			break;
	}
}

/****************************** End Of Module *******************************/

