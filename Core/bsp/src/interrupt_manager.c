#include "interrupt_manager.h"
#include "bsp.h"

/*******************************************************************************
	*
	*Function Name:void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	*Function : timing 10ms interrupt call back function call back function
	*
	*
*******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint8_t tm0,tm1;
    
   if(htim->Instance==TIM17){
    
    tm0++;  //10ms
	tm1++;
 
    
	lcd_t.gTimer_fan_10ms++;
	
    if(tm1>9){ //10*10 = 100ms 
       tm1=0;
       lcd_t.gTimer_colon_ms++ ;
	  
    }

    if(tm0>99){ //100 *10ms = 1000ms = 1s
		tm0=0;
		
		lcd_t.gTimer_error_times++;
	    ctl_t.gTimer_prcoess_iwdg++;
		
		 
		
		
	  }
	
   }


}







