/**********************************************************************
 * MODULENAME.: main.c
 *********************************************************************/
#include <stdint.h>
#include "tm4c123gh6pm.h"



int main(void)
/**********************************************************************
 * FUNCTION: LED follows SWITCH
 *********************************************************************/
{
	int dummy;

	//Enable the GPIO port that is used for the on-board LED
	SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF;

	// Do a dummy read to insert a few cycles after enabling the peripheral
	dummy = SYSCTL_RCGC2_R;

	//Set the direction as output (PF1)
	GPIO_PORTF_DIR_R = 0x02;

	//Enable the GPIO pins for digital function (PF0 and PF1)
	GPIO_PORTF_DEN_R = 0x12;

	//Enable internal pull-up
	GPIO_PORTF_PUR_R = 0x10;

	//Loop forever
    while(1)
    {
    	if (GPIO_PORTF_DATA_R & 0x10)
    		GPIO_PORTF_DATA_R &= ~(0x02);
    	else
    		GPIO_PORTF_DATA_R |= 0x02;

    }
    return (0);
}
