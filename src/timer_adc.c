/*******************************************************************************
* File Name     : timer_adc.c 
* Version       : 1
* Device(s)     : RX63N
* Tool-Chain    : Renesas RX Standard Toolchain 1.0.0
* Description   : Defines the timed ADC sample used in this tutorial.
*******************************************************************************/
/*******************************************************************************
* History : DD.MM.YYYY     Version     Description
*         : 24.02.2012     1.00        First release              
*******************************************************************************/

/*******************************************************************************
* Project Includes
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Board and MCU specific definitions. */
#include "platform.h"
/* Declares LED flash functions used in this file. */
#include "flash_led.h"
/* Provides declarations of functions defined in this file */
#include "timer_adc.h"
/* Provides declarations of ADC functions used in this file. */ 
#include "S12ADC.h" 

#include "cmt_periodic_multi.h"

/*******************************************************************************
Macro Definitions
*******************************************************************************/
#define TIMER_COUNT_100MS   9375 /* 0.1 second with 48MHz pclk / 512 */ 
#define CHANNEL_1   1

/*******************************************************************************
* Local Function Prototypes
*******************************************************************************/
/* AD conversion complete callback function prototype delcaration */
static void cmt_callback_readADC(void);

/*******************************************************************************
* Global Variables
*******************************************************************************/
/* Timer period global variable - time between LED flashes */
volatile uint16_t g_timer_count = TIMER_COUNT_100MS; /* Initial value. */
int draw = 0;
int happy =100, hungry = 0 ; 
/*******************************************************************************
* Function name: timer_adc
* Description  : The function configures a ADC unit and a timer unit. After each
*                timer period the callback function cmt_callback_readADC, is 
*                executed.
* Arguments    : none
* Return value : none
*******************************************************************************/
void timer_adc(void)
{
    /* Prepare the ADC unit for continuous conversion of pot VR1 value. */
    S12ADC_init(); 
    /* Start continuous ADC conversion. */
    S12ADC_start();
    
    /* Prepare a CMT channel as a periodic timer. */
    /* Initialize a CMT one-shot timer. */ 
    cmt_init();
    /* Set up the callback function on cmt channel 0 */   
    cmt_callback_set(CHANNEL_1, &cmt_callback_readADC);
    /* Start 100mS count on cmt channel 0. */
    cmt_start(CHANNEL_1, g_timer_count);
            
} /* End of function timer_adc(). */


/*******************************************************************************
* Function name: cmt_callback_readADC
* Description  : This callback function is to be called from the CMT interrupt.
*                The function reads the ADC conversion value of the potentiometer
*                VR1 setting and the time period of the CMT counter is updated 
*                with a new value proportional to that setting. Then the toggle_led
*                function is called. The result is that the LED toggle rate will 
*                vary based on the pot setting.
* Arguments    : none
* Return value : none
*******************************************************************************/
static void cmt_callback_readADC(void)
{
    uint16_t adc_value;
	int i = rand()/1000 ;
    int j = rand()/100 ;
	draw = 1;
	if(happy > 1 )
	{
		if((j % 3) == 0)
		{
			happy = happy - 3;
		}
		else if((j % 3) == 1)
		{
			happy = happy - 2;
		}
		else if((j % 3) == 2)
		{
			happy = happy - 1;
		}
		else 
		{
			happy = happy - 1;
		}			
	} 
	else
	{
		happy = 0;	
	} 
	if(hungry < 100)
	{
		 if((i % 3) == 0)
		{
			hungry = hungry + 3;
		}
		else if((i % 3) == 1)
		{
			hungry = hungry + 2;
		}
		else if((j % 3) == 2)
		{
			hungry = hungry + 1;
		}
		else 
		{
			hungry = hungry + 1;
		}
	}
	else
	{
		hungry = 100;	
	}	
	cmt_stop(CHANNEL_1); /* Stop the CMT counting. */ 
        
    /* Read the ADC conversion result. */
    adc_value = S12ADC_read();

    /* Recalculate the new timer period to make the flash period visible. */
    /* Max ADC value is 4096 (12 bits). Timer count must not exceed 16 bit value. */  
    g_timer_count = (adc_value * 10)+ 2000; /* Scale the delay and insure non-zero value. */

    /* Start new count on cmt channel 0. */
    cmt_start(CHANNEL_1, g_timer_count);    

    /* Execute the toggle LEDs function */
   // toggle_led();
    
} /* End of function cmt_callback_readADC(). */

     