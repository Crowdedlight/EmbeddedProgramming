#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "../inc/emp_type.h"

#define FCPU                 16000000 	// Hz
#define TIMEOUT              250        // mS
#define SYSTICK_RELOAD_VALUE ((FCPU / 1000) * TIMEOUT) -1

#if (BUFFER_SIZE > 1024)
#error "Buffer er for hoej"
#endif

// Missing definitions in tm4c123gh6pm.h file
#define NVIC_INT_CTRL_PEND_SYST   0x04000000  // Pend a systick int
#define NVIC_INT_CTRL_UNPEND_SYST 0x02000000  // Unpend a systick int

#define SYSTICK_PRIORITY    0x7E



void enable_global_int()
{
  // enable interrupts.
  __asm("cpsie i");
}

void disable_global_int()
{
  // disable interrupts.
  __asm("cpsid i");
}

void SysTick_Handler(void)
/*****************************************************************************
*   Function : See module specification (.h-file).
*****************************************************************************/
{
  // Hardware clears systick int reguest
	  GPIO_PORTF_DATA_R ^= 0x08;

}

void SysTickInit()
{

  // Disable systick timer
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
{
  //
  // Enable the GPIO port that is used for the on-board LED.
  //
  SYSCTL_RCGC2_R = SYSCTL_RCGC2_GPIOF; // Enable Port F

  //
  // Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
  // enable the GPIO pin for digital function.
  //
  GPIO_PORTF_DEN_R  = 0x1F;
  GPIO_PORTF_DIR_R  = 0x0E;
  GPIO_PORTF_PUR_R  = 0x11;
  GPIO_PORTF_DATA_R = 0x00;
  SysTickInit();
  enable_global_int();

  while(1)
  {
    // Do nothing
  }
}
