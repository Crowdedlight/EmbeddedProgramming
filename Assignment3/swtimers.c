/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: swtimers.c
*
* PROJECT....: ECP
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 080219  MoH    Module created.
*
*****************************************************************************/

/***************************** Include files *******************************/
#include "emp_type.h"
#include "events.h"
#include "messages.h"
/*****************************    Defines    *******************************/
#define MAX_SWTIMERS 8

typedef struct timer_descriptor
{
  INT16U timer_value;
  INT8U  event_buffer;
} timer_descriptor;
/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

timer_descriptor POT[MAX_SWTIMERS];  // Pool of timers

/*****************************   Functions   *******************************/

INT16U swtimer( num )
INT8U num;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  return( POT[num].timer_value );
}



void start_swtimer( num, event_buffer, time )
INT8U  num;
INT8U  event_buffer;
INT16U time;        // time/10mSec
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  if( num < MAX_SWTIMERS )
  {
    POT[num].timer_value  = time;
    POT[num].event_buffer = event_buffer;
  }
}


void swt_ctrl(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U i;

  for( i= 0; i<MAX_SWTIMERS; i++ )
  {
    if( POT[i].timer_value )
    {
	    if( !( --POT[i].timer_value ) )
	    {
		    put_msg_event( POT[i].event_buffer, TE_TIMEOUT );
	    }
    }
  }
}

void init_swtimers()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U i;

  for( i= 0; i<MAX_SWTIMERS; i++ )
  {
    POT[i].timer_value  = 0;
    POT[i].event_buffer = 0;
  }
}

/****************************** End Of Module *******************************/












