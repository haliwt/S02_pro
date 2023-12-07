#include "bsp_ctl.h"
#include "bsp.h"




uint8_t (*ptc_state)(uint8_t idata); //adjust of ptc is open or close
uint8_t (*plasma_state)(uint8_t idata); //adjust of plasma is open or close
uint8_t (*ultrasonic_state)(uint8_t idata); //adjust of ultrasoic is open or close
uint8_t (*fan_speed_state)(uint8_t idata); //adjust of win of strong and weak is open or close

uint8_t (*ptc_error_state)(uint8_t err);
uint8_t (*fan_error_state)(uint8_t err);



void bsp_ctl_init(void)
{
   Ptc_State_Handler(Ptc_Default_Handler);
   Plasma_State_Handler(Plasma_Default_Handler);
   Ultrasonic_state_Handler(Ultrasonic_Default_Handler);
   Fan_state_Handler(Fan_Default_Handler);
   Ptc_error_state_Handler(Ptc_Error_Default_Handler);
   Fan_error_state_Handler(Fan_Error_Default_Handler);

}

/*****************************************************************************
 * 
 * Function Name: uint8_t Ptc_State_Handler( uint8_t (*ptc_dat)(uint8_t idat))
 * Function:
 * Input Ref:
 * Return Ref:
 * 
*****************************************************************************/
uint8_t Ptc_State_Handler( uint8_t (*ptc_handler)(uint8_t idat))
{
   	ptc_state = ptc_handler ;

}

/*****************************************************************************
 * 
 * Function Name: void Ptc_Default_Handler(void)
 * Function:
 * Input Ref: idata is ptc is open "1" or "0"  close 
 * Return Ref: close or open 
 * 
*****************************************************************************/
uint8_t Ptc_Default_Handler(uint8_t idata)
{
    static uint8_t ptc_flag;
	if(idata == 0){

	    ptc_flag = open;
	}
	else 
		ptc_flag = close;

	return ptc_flag;

}
/*****************************************************************************
 * 
 * Function Name: uint8_t Plasma_State_Handler(uint8_t(*plasma_handler)(uint8_t ipa))
 * Function:
 * Input Ref: idata is ptc is open "1" or "0"  close 
 * Return Ref: close or open 
 * 
*****************************************************************************/
uint8_t Plasma_State_Handler(uint8_t(*plasma_handler)(uint8_t ipa))
{
	 plasma_state = plasma_handler;

}

uint8_t Plasma_Default_Handler(uint8_t idata)
{
    static uint8_t plasma_flag;
	if(idata == 0){
       plasma_flag = open;
	}
	else 
	  plasma_flag = close;

	return plasma_flag ;

}

/*****************************************************************************
 * 
 * Function Name: void Ptc_Default_Handler(void)
 * Function:
 * Input Ref: idata is ptc is open "1" or "0"  close 
 * Return Ref: close or open 
 * 
*****************************************************************************/
uint8_t Ultrasonic_state_Handler(uint8_t(*ultrasonic_handler)(uint8_t idat))
{
		ultrasonic_state = ultrasonic_handler;
}

uint8_t Ultrasonic_Default_Handler(uint8_t idata)
{
	 static uint8_t ultrasonic_flag;
	if(idata == 0){
       ultrasonic_flag = open;
	}
	else 
	  ultrasonic_flag = close;

	return ultrasonic_flag ;
}
/*****************************************************************************
 * 
 * Function Name: uint8_t Fan_state_Handeler(uint8_t(*fan_handler)(uint8_t idat))
 * Function:
 * Input Ref: idata is ptc is open "1" or "0"  close 
 * Return Ref: close or open 
 * 
*****************************************************************************/
uint8_t Fan_state_Handler(uint8_t(*fan_handler)(uint8_t idat))
{
	fan_speed_state=  fan_handler;
}

uint8_t Fan_Default_Handler(uint8_t idata)
{
	 static uint8_t fan_flag;
	if(idata == 0){
       fan_flag = open;
	}
	else 
	  fan_flag = close;

	return fan_flag ;
}
/*****************************************************************************
 * 
 * Function Name: uint8_t Error_state_Handeler(uint8_t(*error_handler)(uint8_t idat))
 * Function:
 * Input Ref: idata is ptc is open "1" or "0"  close 
 * Return Ref: close or open 
 * 
*****************************************************************************/
uint8_t Ptc_error_state_Handler(uint8_t(*ptc_error_handler)(uint8_t ptc_data))
{
      ptc_error_state = ptc_error_handler;
}

uint8_t Ptc_Error_Default_Handler(uint8_t ptc_error)
{
    static uint8_t error_flag;
	if(ptc_error == 1){
       error_flag = error;
	}
	else{
	  error_flag = good;
	}
    
	return error_flag ;

}
/*****************************************************************************
 * 
 * Function Name: uint8_t Fan_error_state_Handler(uint8_t(*fan_error_handler)(uint8_t fan_data))
 * Function:
 * Input Ref: idata is ptc is open "1" or "0"  close 
 * Return Ref: close or open 
 * 
*****************************************************************************/
uint8_t Fan_error_state_Handler(uint8_t(*fan_error_handler)(uint8_t fan_data))
{
      fan_error_state = fan_error_handler;
}

uint8_t Fan_Error_Default_Handler(uint8_t fan_error)
{
    static uint8_t error_flag;
	if(fan_error == 1){
       error_flag = error;
	}
	else{
	  error_flag = good;
	}
    
	return error_flag ;

}



