/**********************************************************************
 * MODULENAME.: main.c
 *********************************************************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"


#define SYSTICK_RELOAD_VALUE 80000 // 5 ms

//missing definations in .h file
#define NVIC_INT_CTRL_PEND_SYST 	0x04000000 //pend a systick int
#define NVIC_INT_CTRL_UNPEND_SYST	0x02000000 //Unpend a systick int

#define SYSTICK_PRIORITY	0x7E


//Global ints for timer and Color
int click_counter = 0;
//Define array with colors
int colorArray[7] = {0b0000, 0b1000, 0b0100, 0b1100, 0b0010, 0b1010, 0b0110, 0b1110};
int currentColor = 0;
int color_dic = 1;
//Automode Global
int automode = 0;

/**********************************************************************
 * FUNCTION: See module specification (.h file) Interrupt function
 *********************************************************************/
void SysTick_Handler(void)
{
	// Hardware Clears systick int request
	// count for double or long click
	click_counter++;

	if (automode && click_counter >= 40)
	{
		oneClick();
		click_counter = 0;
	}

}


void enable_global_int()
{
	//Enable interrupts
	__asm("cpsie i");
}

void disable_global_int()
{
	//Disable interrupts
	__asm("cpsid i");
}

/**********************************************************************
 * FUNCTION: Setup for Systick Timer
 *********************************************************************/
// Disable systick timer
void SysTickInit()
{
  NVIC_ST_CTRL_R &= ~(NVIC_ST_CTRL_ENABLE);

  // Set current systick counter to reload value
  NVIC_ST_CURRENT_R = SYSTICK_RELOAD_VALUE;
  // Set Reload value, Systick reload register
  NVIC_ST_RELOAD_R = SYSTICK_RELOAD_VALUE;

  // NVIC systick setup, vector number 15
  // Clear pending systick interrupt request
  NVIC_INT_CTRL_R |= NVIC_INT_CTRL_UNPEND_SYST;

  // Set systick priority to 0x10, first clear then set.
  NVIC_SYS_PRI3_R &= ~(NVIC_SYS_PRI3_TICK_M);
  NVIC_SYS_PRI3_R |= (NVIC_SYS_PRI3_TICK_M & (SYSTICK_PRIORITY<<NVIC_SYS_PRI3_TICK_S));

  // Select systick clock source, Use core clock
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_CLK_SRC;

  // Enable systick interrupt
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_INTEN;

  // Enable and start timer
  NVIC_ST_CTRL_R |= NVIC_ST_CTRL_ENABLE;
}


int main(void)
/**********************************************************************
 * FUNCTION: LED follows SWITCH
 *********************************************************************/
{
	//Set start color to none = no LED
	int dummy;
	int swu_pushed = 0;
	int button_presses = 0;

	//Enable the GPIO port that is used for the on-board LED
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

	// Do a dummy read to insert a few cycles after enabling the peripheral
	dummy = SYSCTL_RCGC2_R;

	//Set the direction as output (PF1, PF2 and PF3)
	GPIO_PORTF_DIR_R = 0x0E;

	//Enable the GPIO pins for digital function (PF1, PF2, PF3 and PF4)
	GPIO_PORTF_DEN_R = 0x1E;

	//Enable internal pull-up
	GPIO_PORTF_PUR_R = 0x10;

	//Init Systick
	SysTickInit();

	//Set globals interrupt on
	enable_global_int();

	//Loop forever
    while(1)
    {
    	//Check for button press
    	if (!swu_pushed && !(GPIO_PORTF_DATA_R & 0x10)) //Button pressed
    	{
    		swu_pushed = 1;
    		//Automode toggle
    		if (automode)
    			automode = 0;

    		//Enable interrupt
    		enable_global_int();

    		if (button_presses == 0)
    		{
    			//If first press
    			button_presses = 1;

    			// Reset Timer
    			click_counter = 0;
    		}
    		else if (button_presses == 1 && click_counter < 100) // Double Click
    		{
    			//If second press = double click
    			doubleClick(&color_dic);

    			//Reset
    			button_presses = 0;
    			disable_global_int();
    		}


    	}
    	else if (swu_pushed && (GPIO_PORTF_DATA_R & 0x10)) // button released
    	{
    		//From pushed to non pushed
    		swu_pushed = 0;

    		//Debouncing delay
    		for (int i = 0; i < 1000; i++);

    	}
    	else if (button_presses == 1 && click_counter > 120 && !swu_pushed) // One press
    	{
    		//Have been pressed once, but not as a double click.
    		//Do one click and reset
    		oneClick(color_dic);

    		//reset
    		button_presses = 0;
    		disable_global_int();
    	}
    	else if (button_presses == 1 && click_counter >=400 && swu_pushed) //Check if long press
		{
			//long press enable automode
    		enable_automode();
    		//reset
    		button_presses = 0;
    		//disable_global_int();
		}


    }
    return (0);
}


//Function for button movement
void oneClick()
{
	//Check for direction
	if (color_dic == 1) // Down
		currentColor++;
	else //Up
		currentColor--;

	//Bounderies check
	if (currentColor == 8)
	    {
	    //stay at 7
		currentColor = 7;
	    }
	else if (currentColor == -1)
	{
		//Stay at 0
		currentColor = 0;
	}
	else {
		//Display color
	   	GPIO_PORTF_DATA_R &= ~0b1110;
	   	GPIO_PORTF_DATA_R |= colorArray[currentColor];
	}
}

void doubleClick(int* color_dic)
{
	if (*color_dic == 1)
		*color_dic = 0;
	else
		*color_dic = 1;
}

void enable_automode()
{
	click_counter = 0;
	automode = 1;
}
