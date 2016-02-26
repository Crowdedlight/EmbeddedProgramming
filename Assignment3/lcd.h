/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.h
*
* PROJECT....: Assignment 3
*
* DESCRIPTION: See module specification file (.h-file).
*
* Change Log:
*****************************************************************************
* Date    Id    Change
* YYMMDD
* --------------------
* 160225  SSJ 	Module created.
*
*****************************************************************************/

#ifndef LCD_H_
	#define LCD_H_

/***************************** Include files *******************************/
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "emp_type.h"

/*****************************    Defines    *******************************/
#define LCD_DATA		4
#define LCD_RS			( 1 << 2 )
#define LCD_EN			( 1 << 3 )
#define SW1				( 1 << 4 )

// LCD setup states
#define LCD_SST_FIRST 	1
#define LCD_SST_SECOND 	2
#define LCD_SST_THIRD 	3

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/
void delay();
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Approx. 35 µs delay
******************************************************************************/

void lcd_send(INT8U data);
/*****************************************************************************
*   Input    : 4 bit data to write to LCD data pins
*   Output   : -
*   Function : Writes data to LCD data pins
******************************************************************************/

void lcd_single_command(INT8U cmd);
/*****************************************************************************
*   Input    : 4 bit data to write to LCD data pins
*   Output   : -
*   Function : Sends a 4 bit command to LCD
******************************************************************************/

void lcd_command(INT8U cmd);
/*****************************************************************************
*   Input    : 8 bit data to write to LCD data pins
*   Output   : -
*   Function : Sends an 8 bit command to LCD
******************************************************************************/

void lcd_write(INT8U character);
/*****************************************************************************
*   Input    : Ascii character to write to display
*   Output   : -
*   Function : Writes character on display
******************************************************************************/

void lcd_write_string( INT8U * string );
/*****************************************************************************
*   Input    : String of ascii characters to write to display
*   Output   : -
*   Function : Writes string of characters to display
******************************************************************************/

void lcd_clear_display( void );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Clear display, reset cursor and entry mode
******************************************************************************/

void lcd_set_cursor(INT8U line, INT8U pos);
/*****************************************************************************
*   Input    : Line number, position number
*   Output   : -
*   Function : Set position of cursor
******************************************************************************/

void lcd_setup( void );
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Initialize LCD
******************************************************************************/

BOOLEAN lcd_setup_sm( void );
/*****************************************************************************
*   Input    : -
*   Output   : True when setup is done
*   Function : Initialize LCD with state machine
******************************************************************************/

/****************************** End Of Module *******************************/
#endif /*LCD_H_*/
