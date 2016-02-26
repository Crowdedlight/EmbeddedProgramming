#include "swtimers.h"
#include "tmodel.h"
#include "messages.h"

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

INT8U clock_incr(void)
/*****************************************************************************
*   Input    : Button Event
*   Output   : Update state buffer
*   Function : Increment min. and reset seconds
******************************************************************************/
{
	INT8U sec;
	INT8U min;
	INT8U hour;

	sec = get_msg_state( SSM_CLOCK_SEC );
				if( ++sec == 60 )
				{
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
				}
				put_msg_state( SSM_CLOCK_SEC,sec );
}

INT8U clock_decr(void)
/*****************************************************************************
*   Input    : Button Event
*   Output   : Update state buffer
*   Function : Decrement min. and reset seconds
******************************************************************************/
{
	{
		INT8U sec;
		INT8U min;
		INT8U hour;

		sec = get_msg_state( SSM_CLOCK_SEC );
					if( --sec == 0 )
					{
						sec = 59;
						min = get_msg_state( SSM_CLOCK_MIN );
						if( --min == 0 )
						{
							min = 59;
							hour = get_msg_state( SSM_CLOCK_HOUR );
							if( --hour == 0 )
							{
								hour = 23;
							}
							put_msg_state( SSM_CLOCK_HOUR,hour );
						}
						put_msg_state( SSM_CLOCK_MIN,min );
					}
					put_msg_state( SSM_CLOCK_SEC,sec );
	}
}


/****************************** End Of Module *******************************/
