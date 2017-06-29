
/*******************************************************************************
Includes   <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "platform.h" 
//#include "r_switches.h"
#include "cmt_periodic_multi.h"
#include "timer_adc.h"
//#include "flash_led.h"

/*******************************************************************************
Macro Definitions
*******************************************************************************/
#define TIMER_COUNT_600MS 56250  /* 600mS with 48MHz pclk/512 */
#define MCU_NAME "   RX63N    "
#define CHANNEL_0   0
#define CHANNEL_1   1

/*******************************************************************************
External functions and public global variables. 
*******************************************************************************/



/*******************************************************************************
Private function prototypes and global variables
*******************************************************************************/
void updatescreen(void);
void delay(void);
void delay1(void);
extern int draw;
extern int happy, hungry;
int animate = 1;
int eat = 5;
char *str[50],*str1[50];
/******************************************************************************
* Function name: main
* Description  : Main program function. The function first initialises the debug
*                LCD, and displays the splash screen on the LCD. The function
*                then calls the flash_led, timer_adc and statics_test functions. 
*                These start by flashing the LEDs at a fixed rate until a switch is
*                pressed, then the flash rate varies with the position of the   
*                pot, RV1. Finally, statics_test displays " STATICS " on the    
*                debug LCD, which is replaced with "TEST TEST" a letter at a 
*                time.
* Arguments    : none
* Return value : none
******************************************************************************/
void main(void)
{
	int flag1 = 0,flag2 = 1, set = 0, set1= 0, set2= 0;
	int i,j = 0, k = 0,l = 0;
	int value[10] = {70,60,40,20,10,0};
    /* Initialize the debug LCD on the RSPI bus. */
    lcd_initialize();
    
    /* Clear LCD */
    lcd_clear();
    
    /* Display message on LCD */
    lcd_display(LCD_LINE1, "  RENESAS   ");
    lcd_display(LCD_LINE2, MCU_NAME);

    cmt_init(); /* Initialize the CMT unit for application timing tasks. */ 
	timer_adc();
	lcd_clear();	
    while (1)
    {
		if(SW1 == 0)
		{
			delay();
		    if(SW1 == 0)
			{
				flag1 = flag1 + 1;
				set = set + 1; 
			}
		}
		if(SW2 == 0)
		{
			delay();
		    if(SW2 == 0)
			{
				set1 = set1 + 1; 
				flag2 = flag2 - 1;
				if(flag2 == 0)
					flag2 = 3;
			}
		}
		if(SW3 == 0)
		{
			delay();
		    if(SW3 == 0)
			{
				set2 = set2 + 1; 
				flag2 = flag2 + 1;
				if(flag2 == 4)
					flag2 = 0;
			}
		}	
		delay();
		if(flag1 % 2 == 1)
		{	
			switch(flag2)
			{
				case 1 :
						delay();
						delay();
						if(set > 1)
						{
							j = 1;
							//flag1 = 0;						
						}	
						delay();
						if(j == 0)
						{	
							set2 = 0;
							set1 = 0;
							lcd_clear();
							Set_Font_8_by_8();
							lcd_display(LCD_LINE1, "MENU -  ");
							lcd_display(LCD_LINE2,">.Feed Pet");
		    				lcd_display(LCD_LINE3,"2.Play Pet ");
							lcd_display(LCD_LINE4,"3. Exit");
							sprintf(str,"Happy:%d",happy);
							sprintf(str1,"Hungry:%d",hungry);
							lcd_display(LCD_LINE6, str);
							lcd_display(LCD_LINE7,str1);
						}
						else
						{
							k = k + 1;
							if( hungry < 0 )
							{
								l = 1;
								j = 0;
								set = 0; 
								lcd_clear();
								hungry = 0;
								happy = happy + 15;
								flag1 = 0;
							}
							else
							{	
								delay();
								delay();
								lcd_clear();
								Set_Font_Bitmap();
								Set_LCD_Pos(20,5);
								// Select Animation Frame
								if(eat == 5)
								eat = 6;
								else
								eat = 5;
								Set_LCD_Char(eat);
								//draw = 0;
								hungry = hungry - 5;
							}			
						}
						break;
		
				case 2 :
						delay();
						delay();
						if(set > 1)
						{
							j = 1;
							//flag1 = 0;						
						}	
						delay();
						if(j == 0)
						{
						set2 = 0;
						set1 = 0;		
						lcd_clear();
						Set_Font_8_by_8();
						lcd_display(LCD_LINE1, "MENU -  ");
						lcd_display(LCD_LINE2,"1.Feed Pet");
		    			lcd_display(LCD_LINE3,">.Play Pet");
						lcd_display(LCD_LINE4,"3. Exit");
						sprintf(str,"Happy:%d",happy);
						sprintf(str1,"Hungry%d",hungry);
						lcd_display(LCD_LINE6, str);
						lcd_display(LCD_LINE7,str1);
						}
						else
						{
							int random = rand()/100;
							lcd_clear();
							Set_Font_Bitmap();
							if((random % 2) == 0)
							{
								Set_LCD_Pos(40,5);
							}
							else
							{
								Set_LCD_Pos(40,15);	
							}
							Set_LCD_Char(1);
							delay();
							delay();
							delay();
							delay();
							delay();
							delay();
							delay();
							delay();
							if(SW2 == 0)
							{
								delay();
								if(SW2 ==0)
								{
									lcd_clear();
									Set_Font_Bitmap();
									Set_LCD_Pos(5,5);
									Set_LCD_Char(9);
									delay1();
									delay();
									lcd_clear();
									Set_Font_Bitmap();
									Set_LCD_Pos(20,5);
									Set_LCD_Char(9);
									delay1();
									delay();
									lcd_clear();
									Set_Font_Bitmap();
									Set_LCD_Pos(40,5);
									Set_LCD_Char(8);
									delay1();
									j = 0;
									set = 0; 
									set1 = 0; 
									lcd_clear();
									hungry = hungry + 15;;
									happy = happy + 20;
									if(happy > 100)
									{
										happy = happy - 5;
									}
									flag1 = 0;
								}	
							}
							if(SW3 == 0)
							{
								delay();
								if(SW3 == 0 )
								{
									lcd_clear();
									Set_Font_Bitmap();
									Set_LCD_Pos(5,20);
									Set_LCD_Char(9);
									delay1();
									delay();
									lcd_clear();
									Set_Font_Bitmap();
									Set_LCD_Pos(20,20);
									Set_LCD_Char(9);
									delay1();
									delay();
									lcd_clear();
									Set_Font_Bitmap();
									Set_LCD_Pos(40,20);
									Set_LCD_Char(8);
									delay1();
									j = 0;
									set = 0;
									set2 = 0; 
									lcd_clear();
									hungry = hungry + 15;
									happy = happy + 20; 
									if(happy > 100)
									{
										happy = happy - 5;
									}	
									flag1 = 0;								
								}
							}	 			
						}
						break;
								
				case 3 :
						set2 = 0;
						set1 = 0;
						lcd_clear();
						Set_Font_8_by_8();
						lcd_display(LCD_LINE1, "MENU -  ");
						lcd_display(LCD_LINE2,"1.Feed Pet");
		    			lcd_display(LCD_LINE3,"2.Play Pet ");
						lcd_display(LCD_LINE4,">. Exit");
						sprintf(str, "Happy:%d",happy);
						sprintf(str1, "Hungry:%d",hungry);
						lcd_display(LCD_LINE6, str);
						lcd_display(LCD_LINE7,str1);
						 if(set > 1)
						{
							set = 0;
							flag1 = 0;
						}
						break;
			}
		}	
		else
		{
			if(draw)
	    	{
				if(hungry == 100)
				{
					cmt_stop(CHANNEL_1);
					lcd_clear();
					Set_Font_Bitmap();
					Set_LCD_Pos(20,5);
					Set_LCD_Char(7);
					Set_Font_8_by_8();
					sprintf(str, "Happy:%d",happy);
					sprintf(str1, "Hungry:%d",hungry);
					lcd_display(LCD_LINE6, str);
					lcd_display(LCD_LINE7,str1);	
				}
				else if(happy == 0)	
				{
					cmt_stop(CHANNEL_1);
					for(i = 0 ; i < 6 ; i++)
					{
						lcd_clear();
						Set_Font_Bitmap();
						Set_LCD_Pos(value[i],5);
						Set_LCD_Char(1);
						Set_Font_8_by_8();
						sprintf(str, "Happy:%d",happy);
						sprintf(str1, "Hungry:%d",hungry);
						lcd_display(LCD_LINE6, str);
						lcd_display(LCD_LINE7,str1);
						j = j + 1;
						delay1();
					}
					if(j > 5)
					{
						lcd_clear();
				    	Set_Font_8_by_8();
						lcd_display(LCD_LINE6,"Bye Bye");
						delay1();
					}		
				}
				else
				{
					if((hungry < 100) && (happy > 0))
					{
						lcd_clear();
						updatescreen();
						Set_Font_8_by_8();
						sprintf(str, "Happy:%d",happy);
						sprintf(str1, "Hungry:%d",hungry);
						lcd_display(LCD_LINE6, str);
						lcd_display(LCD_LINE7,str1);
					}	
				}		
			}
		}					
	}
} /* End of function main(). */


void updatescreen(void)
{
	lcd_clear();
	Set_Font_Bitmap();
	Set_LCD_Pos(20,5);
	// Select Animation Frame
	if(animate == 1)
		animate = 2;
	else
		animate = 1;
	Set_LCD_Char(animate);
	draw = 0;
}	

void delay() //Delay loop
{
	int i,j;
	for(i=0;i<300;i++)
		for(j=0;j<5000;j++);	
}	

void delay1() // Long time Delay loop
{
	int i,j;
	for(i=0;i<15000;i++)
		for(j=0;j<5000;j++);	
}	
	