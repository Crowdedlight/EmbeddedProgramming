

/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: clock_setup.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: Setup the time.
*
******************************************************************************/

#ifndef CLOCK_SETUP_H_
#define CLOCK_SETUP_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

INT8U clock_incr(void);
/*****************************************************************************
*   Input    : Button Event
*   Output   : Update state buffer
*   Function : Increment min. and reset seconds
******************************************************************************/

INT8U clock_decr(void);
/*****************************************************************************
*   Input    : Button Event
*   Output   : Update state buffer
*   Function : Decrement min. and reset seconds
******************************************************************************/


/****************************** End Of Module *******************************/
#endif /*CLOCK_SETUP_H_*/




