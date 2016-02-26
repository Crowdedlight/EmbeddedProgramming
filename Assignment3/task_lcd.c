/*****************************************************************************
* University of Southern Denmark
* Embedded Programming (EMP)
*
* MODULENAME.: task_lcd.c
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
#include "task_lcd.h"
/*****************************    Defines    *******************************/

/*****************************   Constants   *******************************/

/*****************************   Functions   *******************************/

void task_lcd ( INT8U TASK_NUM )
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Task for our LCD
******************************************************************************/
{
    static INT8U lcd_state = LCD_INIT;
    
    //Get Events
    INT8U event = get_msg_event( SEB_LCD_EVENT );

    if( !event )
    {
        if ( get_msg_event( SEB_TO_LCD ) )
        {
        	start_swtimer( ST_LCD, SEB_TO_LCD, MILLISEC(500) );
        	event = TE_TIMEOUT;
        }
    }
    
    switch ( lcd_state )
    {
    	case LCD_INIT:
    		if( lcd_setup_sm() )
    		{
    			lcd_state = LCD_RUNNING;
    			start_swtimer( ST_LCD, SEB_TO_LCD, MILLISEC(500) );
    			lcd_update();
    		}
    	break;

        case LCD_RUNNING:
            
            switch(event)
            {
                case TE_TIMEOUT:
                    //Toggle ":" to display blink
                    lcd_toggle_col();
                break;
                
                case LCDE_STOP:
                    //Set state paused and turn colon on
                    lcd_state = LCD_PAUSED;
                    lcd_set_cursor(POS_LINE, POS_COL);
                    lcd_write(':');
                break;
                
                case LCDE_UPDATE:
                    //Update time
                    lcd_update();
                break;
                
                default:
                break;
            }
            
        break;
        
        case LCD_PAUSED:
        
            switch(event)
            {                
                case LCDE_START:
                    //Set state running
                    lcd_state = LCD_RUNNING;
                break;
                
                case LCDE_UPDATE:
                    lcd_update();
                break;
                
                default:
                break;
            }
        
        break;
        
        default:        
        break;
    }
}


void lcd_toggle_col()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Function to make Colon blink
******************************************************************************/
{
    static INT8U on = 1;
    
    //Set Cursor position
    lcd_set_cursor ( POS_LINE, POS_COL);
    
    if (on)
    {
        //Send space to display
        lcd_write( ' ' );
        on = 0;
    }
    else
    {
        //Send ':' to LCD
        lcd_write(':');
        on = 1;
    }
}

void lcd_update()
/*****************************************************************************
*   Input    : -
*   Output   : -
*   Function : Function to update time
******************************************************************************/
{
    //Get Time
    INT8U hh = get_msg_state( SSM_CLOCK_HOUR );
    INT8U mm = get_msg_state( SSM_CLOCK_MIN );
    
    //Split time to 2 chars
    INT8U hh_arr[3] = { hh / 10 + '0', hh % 10 + '0' };		// Size = 3 to insert terminating NULL
    INT8U mm_arr[3] = { mm / 10 + '0', mm % 10 + '0' };
    
    //update hour
    lcd_set_cursor(POS_LINE, POS_HH);
    lcd_write_string(hh_arr);
    //lcd_write(hh_arr[0]);
    //lcd_write(hh_arr[1]);
    
    //Update min
    lcd_set_cursor(POS_LINE, POS_MM);
    lcd_write_string( mm_arr);
    //lcd_write(mm_arr[0]);
    //lcd_write(mm_arr[1]);
    
}
/****************************** End Of Module *******************************/


