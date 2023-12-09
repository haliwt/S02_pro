#ifndef  	__BSP_H_
#define 	__BSP_H_
#include "main.h"

#include "interrupt_manager.h"
#include "adc.h"
#include "iwdg.h"
#include "tim.h"
#include "bsp_adc.h"
#include "bsp_led.h"
#include "bsp_lcd.h"
#include "bsp_buzzer.h"
#include "bsp_key.h"
#include "bsp_sensor.h"
#include "bsp_ultrasonic.h"
#include "bsp_delay.h"
#include "bsp_ctl.h"
#include "bsp_fan.h"
#include "bsp_plasma.h"
#include "bsp_ptc.h"


typedef struct {

   uint8_t set_temp_confirm ;
   uint8_t gdht11_temperature;

   int8_t set_timer_timing_hours;
   int8_t set_timer_timing_minutes;


   uint8_t gTimer_run_adc;
   uint8_t gTimer_run_dht11;
   uint8_t gTimer_run_display;
   uint8_t gTimer_run_one_mintue ;
   
   uint16_t gTimer_run_total;
   uint16_t gTimer_run_time_out;

   uint8_t gTimer_works_counter;
   uint8_t gTimer_display_works_hours;
   uint8_t gTimer_display_works_minutes;
   uint8_t gTimer_timer_Counter;
   uint8_t gTimer_set_timer ;


}BSP_process_t;

extern BSP_process_t gProcess_t;

void bsp_Idle(void);

void mainboard_process_handler(void);



#endif 

