#ifndef __BSP_CTL_H
#define __BSP_CTL_H
#include "main.h"


typedef enum{

   uint8_t open,
   uint8_t close
  
}hard_state;


typedef enum{

   uint8_t good,
   uint8_t error

}hard_error_state;

typedef struct _bsp_ctl{

    uint8_t gTimer_prcoess_iwdg;
	uint8_t gTimer_process_display;

}bsp_ctl;

extern bsp_ctl ctl_t;

extern uint8_t (*ptc_state)(uint8_t idata); //adjust of ptc is open or close
extern uint8_t (*plasma_state)(uint8_t idata); //adjust of plasma is open or close
extern uint8_t (*ultrasonic_state)(uint8_t idata); //adjust of ultrasoic is open or close
extern uint8_t (*fan_speed_state)(uint8_t idata); //adjust of win of strong and weak is open or close

extern uint8_t (*ptc_error_state)(uint8_t err);
extern uint8_t (*fan_error_state)(uint8_t err);


void bsp_ctl_init(void);


uint8_t Ptc_State_Handler( uint8_t (*ptc_handler)(uint8_t idat));
uint8_t Plasma_State_Handler(uint8_t(*plasma_handler)(uint8_t ipa));
uint8_t Ultrasonic_state_Handler(uint8_t(*ultrasonic_handler)(uint8_t idat));
uint8_t Fan_state_Handler(uint8_t(*fan_handler)(uint8_t idat));

uint8_t Ptc_error_state_Handler(uint8_t(*error_handler)(uint8_t idat));
uint8_t Fan_error_state_Handler(uint8_t(*fan_error_handler)(uint8_t fan_data));




uint8_t Ptc_Default_Handler(uint8_t idata);
uint8_t Plasma_Default_Handler(uint8_t idata);
uint8_t Ultrasonic_Default_Handler(uint8_t idata);
uint8_t Fan_Default_Handler(uint8_t idata);

uint8_t Ptc_Error_Default_Handler(uint8_t idata);

uint8_t Fan_Error_Default_Handler(uint8_t fan_error);













#endif 
