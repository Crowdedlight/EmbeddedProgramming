/*****************************************************************************
* University of Southern Denmark
* Embedded C Programming (ECP)
*
* MODULENAME.: tmodel.h
*
* PROJECT....: ECP
*
* DESCRIPTION: Defines the element of the task model..
*
*
*****************************************************************************/

#ifndef _TMODEL_H_
#define _TMODEL_H_

// Tasks.
// ------
#define TASK_SW_TIMERS 11
#define TASK_SET_TIME 12
#define TASK_BUTTON 13
#define TASK_RTC 14
#define TASK_LCD 15

// Interrupt Service Routines.
// ---------------------------
#define ISR_TIMER 21

// Shared State Memory.
// --------------------
#define SSM_CLOCK_SEC  31	//
#define SSM_CLOCK_MIN  32	//
#define SSM_CLOCK_HOUR 33	//

// Shared Event Buffers.
// ---------------------
#define SEB_BUTTON_EVENT 41
#define SEB_TO_BUTTON 	 42 // Time Out
#define SEB_TO_LCD 		 43 // Time Out
#define SEB_LCD_EVENT 	 44	//
#define SEB_CLOCK_EVENT  47	// Time Out

// Software Timers.
// ----------------
#define ST_BUTTON   1
#define ST_CLOCK    2
#define ST_LCD		3

#endif /* _TMODEL_H_ */
