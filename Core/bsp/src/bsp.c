#include "bsp.h"


BSP_process_t gProcess_t;
static uint8_t Works_Time_Out(void);
static void Mainboard_Action_Fun(void);
static void Mainboard_Fun_Stop(void);


uint8_t  fan_continue_flag;

/*
*********************************************************************************************************
*	函 数 名: bsp_Idle
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_Idle(void)
{
	/* --- 喂狗 8s input reset */
    if(gctl_t.gTimer_prcoess_iwdg > 5){
		gctl_t.gTimer_prcoess_iwdg =0;
    	iwdg_feed();

    }

	/* --- 让CPU进入休眠，由Systick定时中断唤醒或者其他中断唤醒 */

	/* 例如 emWin 图形库，可以插入图形库需要的轮询函数 */
	//GUI_Exec();

	/* 例如 uIP 协议，可以插入uip轮询函数 */
	//TOUCH_CapScan();
	
	//MODH_Poll();
}
/*
*********************************************************************************************************
*	函 数 名: void mainboard_process_handler(void)
*	功能说明: 空闲时执行的函数。一般主程序在for和while循环程序体中需要插入 CPU_IDLE() 宏来调用本函数。
*			 本函数缺省为空操作。用户可以添加喂狗、设置CPU进入休眠模式的功能。
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void mainboard_process_handler(void)
{
    static uint8_t step_process,first_power_up;

	if( gkey_t.key_sound_flag == key_sound){
		gkey_t.key_sound_flag =0;
		Buzzer_KeySound();

    }

	switch(gkey_t.key_power){

      case power_off:

	    step_process=0;
	    LED_Mode_Off();
	   
	    Breath_Led();
        Ptc_Off();
		Ultrasonic_Pwm_Stop();
		Plasma_Off();
	
        if(first_power_up==1){
           if(gkey_t.gTimer_power_off < 61){
                Fan_Run();
				LCD_Display_Wind_Icon_Handler();

		   }
		   else{
              first_power_up =0;
			   Fan_Stop();
		       Backlight_Off();
		       Lcd_Display_Off();
			   
		   }

		}

		if( first_power_up ==0){

		  Fan_Stop();
		  Backlight_Off();
		  Lcd_Display_Off();


		}


	  break;


	  case power_on:

        switch(step_process){


		  case 0:
              //led on 
              first_power_up=1;
		      LED_Mode_On();
		      LED_Power_On();
		      Backlight_On();
		  
			  Update_DHT11_Value();
		      Lcd_Display_Detials();

			  //fan on
			  Mainboard_Action_Fun();
		  
		    step_process = 1;


		  break;

		  

		  case 1: //run display

		    if(gProcess_t.gTimer_run_display > 30){ //30*10 =300ms flash
			     gProcess_t.gTimer_run_display=0;
				 
			     Lcd_Display_Detials();
 
            }

		     step_process=2;

		  case 2:   //run dht11 display 

          if(gProcess_t.gTimer_run_dht11 > 36){
		  	gProcess_t.gTimer_run_dht11 =0;
	        Update_DHT11_Value();

          }
           step_process=3;
		  
          break;

		  case 3: //detected ptc temperature value and fan if fault

		  if(gProcess_t.gTimer_run_adc > 10 && gProcess_t.gTimer_run_adc < 12){ //3 minutes 120s
				
			  Get_PTC_Temperature_Voltage(ADC_CHANNEL_1,5);
			  HAL_Delay(2);
					
          }

		  if(gProcess_t.gTimer_run_adc > 18){ //2 minute 180s
				gProcess_t.gTimer_run_adc=0;

				Get_Fan_Adc_Fun(ADC_CHANNEL_0,5);
				HAL_Delay(2);
	               

		 }

		  step_process=4;

		  break;

		  case 4: //check works times 
			  if(gProcess_t.gTimer_run_total > 119){ //120 minutes
			       gProcess_t.gTimer_run_total =0;
				   gProcess_t.gTimer_run_time_out=0;  //time out recoder start 10 minutes
				   gProcess_t.gTimer_run_one_mintue =0;
				   fan_continue_flag=0;
				   step_process=5;
			  
		         
			    }
			    else{
				  step_process=1;

              }

		  break;

		  case 5: //works have a rest ten minutes

		       if(Works_Time_Out()==1){

			        step_process=1;

			   }
			   else{

			      step_process=5;

			   }


		  break;

		  


	     }

        
	  break;

	 


    }

}


/*
*********************************************************************************************************
*	函 数 名: static uint8_t Works_Time_Out(void)
*	功能说明: 主板工作2小时，停止工作10分钟
*			 
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static uint8_t Works_Time_Out(void)
{
	if(gProcess_t.gTimer_run_time_out < 11){
		
		Mainboard_Fun_Stop();
		 
    }

	if(gProcess_t.gTimer_run_one_mintue < 60 && ( fan_continue_flag ==0)){

		Fan_Run();

	}

	if(gProcess_t.gTimer_run_one_mintue > 60){

	     fan_continue_flag=1;

         Fan_Stop();
	 }

	if(gProcess_t.gTimer_run_time_out > 10){ //10 minutes
		gProcess_t.gTimer_run_time_out=0;
		gProcess_t.gTimer_run_total=0;

		Mainboard_Action_Fun();
		

		return 1;


	}
	else{
      
	  return 0;

	}

}


/*
*********************************************************************************************************
*	函 数 名: static void Mainboard_Action_Fun(void)
*	功能说明: 主板工作：功能动作输出
*			 
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void Mainboard_Action_Fun(void)
{
    Ptc_On();
	Ultrasonic_Pwm_Output();
	Fan_Run();
	Plasma_On();
	
	
}

/*
*********************************************************************************************************
*	函 数 名: static void Mainboard_Action_Fun(void)
*	功能说明: 主板工作：功能动作输出
*			 
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void Mainboard_Fun_Stop(void)
{
   Ptc_Off();

   Ultrasonic_Pwm_Stop();
   Fan_Stop();
   Plasma_Off();


}


