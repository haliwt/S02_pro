#include "bsp_key.h"
#include "bsp.h"

key_fun_t gkey_t;

uint8_t key_mode_change;
uint8_t set_up_temperature_value ;
int8_t set_timer_dispTime_minutes;
int8_t set_timer_dispTime_hours;

/*
  * key interrupt call back function 

*/

void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{

  static uint8_t key_mode_times;
   switch(GPIO_Pin){

   case KEY_POWER_Pin:

      if(gkey_t.key_power == power_off){
	  	   gkey_t.key_sound_flag = key_sound;
           gkey_t.key_power = power_on;

      }
	  else{
	  	  gkey_t.key_sound_flag = key_sound;
          gkey_t.key_power = power_off;
	      gkey_t.gTimer_power_off = 0;

	  }


   break;

   case KEY_MODE_Pin:
   if(gkey_t.key_power == power_on){
   	  gkey_t.key_sound_flag = key_sound;
      key_mode_times = key_mode_times ^ 0x01;
      if(key_mode_times == 1){
          gkey_t.key_mode = mode_set_timer;
          key_mode_change = mode_set_timer;
      }
      else{

         gkey_t.key_mode = mode_confirm;
         key_mode_change = 0;
      }
   }
   break;


   case KEY_UP_Pin:
       if(gkey_t.key_power == power_on){
	   	
        gkey_t.key_sound_flag = key_sound;
		  switch(key_mode_change){

		    case 0:  //set temperature value 
            set_up_temperature_value ++;
	         if(set_up_temperature_value < 20){
				    set_up_temperature_value=20;
				}
				
				if(set_up_temperature_value > 40)set_up_temperature_value= 20;
				
			   glcd_t.number3_low = set_up_temperature_value / 10 ;
            glcd_t.number3_high = set_up_temperature_value / 10 ;
			   glcd_t.number4_low  =set_up_temperature_value % 10; //
            glcd_t.number4_high = set_up_temperature_value % 10; //

            gkey_t.key_select = set_timer_confirm;
            gkey_t.gTimer_key_temp_timing=0;
			
			break;

			case mode_set_timer: //set timer timing value 
			
				 if(set_timer_dispTime_hours!=24)
				 		set_timer_dispTime_minutes =  set_timer_dispTime_minutes + 30;
				 else if(set_timer_dispTime_hours ==24)
				 	    set_timer_dispTime_minutes =  set_timer_dispTime_minutes + 60;

			    if(set_timer_dispTime_minutes >59){
					     set_timer_dispTime_hours++;
		             if(set_timer_dispTime_hours ==24){
						    set_timer_dispTime_minutes=0;
					}
					else if(set_timer_dispTime_hours >24){

					   set_timer_dispTime_hours =0;
					   set_timer_dispTime_minutes=0;


					}
					else{

					   set_timer_dispTime_minutes=0;


					}
						
			     }
            
                  //display hours
                  glcd_t.number5_low = set_timer_dispTime_hours / 10 ;
                  glcd_t.number5_high = set_timer_dispTime_hours / 10 ;

                  glcd_t.number6_low  =set_timer_dispTime_hours % 10; //
                  glcd_t.number6_high = set_timer_dispTime_hours % 10; //
                   //dispaly minutes 
                  glcd_t.number7_low =  set_timer_dispTime_minutes /10;
                  glcd_t.number7_high =  set_timer_dispTime_minutes /10;

                  glcd_t.number8_low =  set_timer_dispTime_minutes %10;
                  glcd_t.number8_high =  set_timer_dispTime_minutes %10;

                 gkey_t.gTimer_set_timer =0;
            }
         
       }
   break;

   case KEY_DOWN_Pin:
     if(gkey_t.key_power == power_on){

	     gkey_t.key_sound_flag = key_sound;
        
         switch(key_mode_change){

         case 0: //set temperature 

         set_up_temperature_value--;
			if(set_up_temperature_value<20) set_up_temperature_value=40;
	        else if(set_up_temperature_value >40)set_up_temperature_value=40;

           if(set_up_temperature_value > 40)set_up_temperature_value= 20;
				
			   glcd_t.number3_low = set_up_temperature_value / 10 ;
            glcd_t.number3_high = set_up_temperature_value / 10 ;
			   glcd_t.number4_low  =set_up_temperature_value % 10; //
            glcd_t.number4_high = set_up_temperature_value % 10; //

            gkey_t.key_select = set_timer_confirm;
            gkey_t.gTimer_key_temp_timing=0;

         break;

         case mode_set_timer: //set timer timing value 
            set_timer_dispTime_minutes =  set_timer_dispTime_minutes-30;
		        if(set_timer_dispTime_minutes < 0){
					set_timer_dispTime_hours--;
                   if(set_timer_dispTime_hours <0){
                         
				      set_timer_dispTime_hours=24;
					  set_timer_dispTime_minutes=0;

				   }
				   else{

				     set_timer_dispTime_minutes =30;
               }
				  
				}

             //display hours
                  glcd_t.number5_low = set_timer_dispTime_hours / 10 ;
                  glcd_t.number5_high = set_timer_dispTime_hours / 10 ;

                  glcd_t.number6_low  =set_timer_dispTime_hours % 10; //
                  glcd_t.number6_high = set_timer_dispTime_hours % 10; //
                   //dispaly minutes 
                  glcd_t.number7_low =  set_timer_dispTime_minutes /10;
                  glcd_t.number7_high =  set_timer_dispTime_minutes /10;

                  glcd_t.number8_low =  set_timer_dispTime_minutes %10;
                  glcd_t.number8_high =  set_timer_dispTime_minutes %10;

                 gkey_t.gTimer_set_timer =0;

         break;
 
         }
     }

   break;


   }



}




