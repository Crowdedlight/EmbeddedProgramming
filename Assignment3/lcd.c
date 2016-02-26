/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: lcd.c
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

/***************************** Include files *******************************/
#include "lcd.h"

/*****************************   Variables   *******************************/

/*****************************   Functions   *******************************/

void delay()
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	for(volatile INT8U i = 0; i<50; i++); // Approx. 35 us delay
}

void lcd_send(INT8U data)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	GPIO_PORTC_DATA_R &= 0x0F;				// Clear data pins
	GPIO_PORTD_DATA_R |= LCD_EN;			// Enable high
	GPIO_PORTC_DATA_R |= data << LCD_DATA;	// Send low nibble
	GPIO_PORTD_DATA_R &= ~LCD_EN;			// Enable low
}

void lcd_single_command(INT8U cmd)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	GPIO_PORTD_DATA_R &= ~LCD_RS;	// Select instruction register
	delay();
	lcd_send( cmd );				// Send command to LCD
}

void lcd_command(INT8U cmd)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	GPIO_PORTD_DATA_R &= ~LCD_RS; 	// Select instruction register
	delay();
	lcd_send( cmd >> 4 );			// Send high nibble to LCD
	//delay();
	lcd_send( cmd & 0x0F );			// Send low nibble to LCD
	//delay();
}

void lcd_write(INT8U character)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	GPIO_PORTD_DATA_R |= LCD_RS; 	// Select data register
	delay();
	lcd_send( character >> 4 );		// Send high nibble to LCD
	//delay();
	lcd_send( character & 0x0F );	// Send low nibble to LCD
	//delay();
}

void lcd_write_string( INT8U * string )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	INT8U i = 0;
	while( string[i] != 0 )
	{
		lcd_write( string[i++] );
	}
}

void lcd_clear_display( void )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	lcd_command(0x01);									//Clear display
	for( volatile int temp = 0; temp < 5000; temp++ );	// Approx. 2 ms delay
}

void lcd_set_cursor(INT8U line, INT8U pos)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	if( line == 1 )
	{
		lcd_command( ( 1 << 7 ) | pos );
	}
	else if( line == 2 )
	{
		lcd_command( ( 1 << 7 ) | ( pos + 40 ) );
	}
}

void lcd_setup( void )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{

	//Setup LCD pins
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;		// Enables clock for GPIOD
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;		// Enables clock for GPIOC

	GPIO_PORTC_DIR_R |= 0xF0;					// Set PC4:7 (LCD data pins) as outputs
	GPIO_PORTD_DIR_R |= 0x0C;					// Set PD2:3 (LCD_RS, LCD_EN) as outputs

	GPIO_PORTC_DEN_R |= 0xF0;					// Digital Enable PC4:7 (LCD data pins)
	GPIO_PORTD_DEN_R |= 0x0C;					// Digital Enable PD2:3 (LCD_RS, LCD_EN)

	// LCD initialize
	for( volatile INT32U i; i < 30000; i++ ); 	// Wait for more than 15 ms
	lcd_single_command(0x03);
	for( volatile INT32U i; i < 10000; i++ ); 	// Wait for more than 4.1 ms
	lcd_single_command( 0x03 );
	lcd_single_command( 0x03 );
	lcd_single_command( 0x02 );
	lcd_command( 0x28 ); 						// 4 bit mode, 2 lines, 5x8 font
	lcd_command( 0x08 );						// Display off
	lcd_command( 0x0C ); 						// Display on, hide cursor
	lcd_clear_display(); 						// Clear display, reset cursor position and direction
	lcd_command(0x06);							// Entry mode
}


BOOLEAN lcd_setup_sm( void )
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
	static INT8U lcd_setup_state  = LCD_SST_FIRST;
	static INT32U lcd_setup_timer = 0;
	BOOLEAN done = 0;

	switch ( lcd_setup_state )
	{
		case LCD_SST_FIRST:
			//Setup LCD pins
			SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC;	// Enables clock for GPIOD
			SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;	// Enables clock for GPIOC

			GPIO_PORTC_DIR_R |= 0xF0;				// Set PC4:7 (LCD data pins) as outputs
			GPIO_PORTD_DIR_R |= 0x0C;				// Set PD2:3 (LCD_RS, LCD_EN) as outputs

			GPIO_PORTC_DEN_R |= 0xF0;				// Digital Enable PC4:7 (LCD data pins)
			GPIO_PORTD_DEN_R |= 0x0C;				// Digital Enable PD2:3 (LCD_RS, LCD_EN)

			lcd_setup_timer = 3;					// 15 ms if systick is 5 ms
			lcd_setup_state = LCD_SST_SECOND;
			break;
		case LCD_SST_SECOND:
			if( ! --lcd_setup_timer )
			{
				lcd_single_command(0x03);
				lcd_setup_state = LCD_SST_THIRD;
				break;								// No delay needed if systick is 5 ms
			}
			break;
		case LCD_SST_THIRD:
			lcd_single_command( 0x03 );
			lcd_single_command( 0x03 );
			lcd_single_command( 0x02 );
			lcd_command( 0x28 ); 						// 4 bit mode, 2 lines, 5x8 font
			lcd_command( 0x08 );						// Display off
			lcd_command( 0x0C ); 						// Display on, hide cursor
			lcd_clear_display(); 						// Clear display, reset cursor and entry mode
			done = 1;
			break;
		default:
			break;
	}

	return done;
}

/****************************** End Of Module *******************************/
