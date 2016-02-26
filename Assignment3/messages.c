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
#include "messages.h"

/*****************************    Defines    *******************************/
#define MAX_MSG 64

/*****************************   Constants   *******************************/

/*****************************   Variables   *******************************/

INT8U   msg_event[MAX_MSG];
INT8U   msg_state[MAX_MSG];

/*****************************   Functions   *******************************/

INT8U get_msg_event( num )
INT8U num;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U result = 0;

  if( num < MAX_MSG )
  {
    if( msg_event[num] )
	  {
	    result = msg_event[num];
	    msg_event[num] = 0;
	  }
  }
  return( result );
}



void put_msg_event( num, event )
INT8U  num;
INT8U  event;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  if( num < MAX_MSG )
    msg_event[num] = event;
}

INT8U get_msg_state( num )
INT8U num;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  INT8U result = 0;

  if( num < MAX_MSG )
  {
    result = msg_state[num];
  }
  return( result );
}



void put_msg_state( num, state )
INT8U  num;
INT8U  state;
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  if( num < MAX_MSG )
    msg_state[num] = state;
}

