/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: events.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Test.
*
* Change Log:
******************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 090215  MoH   Module created.
*
*****************************************************************************/

#ifndef EVENTS_H_
#define EVENTS_H_

/***************************** Include files *******************************/

/*****************************    Defines    *******************************/
// Events.
// -------

// General Events
// --------------
#define GE_NUM_EVENT      0

// Button Events
// -------------
#define BE_SINGLE_PUSH   1
#define BE_DOUBBLE_PUSH  2
#define BE_LONG_PUSH     3

// LCD Events
#define LCDE_START	1
#define LCDE_STOP	2
#define LCDE_UPDATE	3

// Timer Events
// ------------
#define TE_TIMEOUT      10
/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

/****************************** End Of Module *******************************/
#endif /*EVENTS_H_*/
