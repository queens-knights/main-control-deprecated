#include "cmsis_os.h"
#include "stdlib.h"

#include "rm_hal_lib.h"
#include "relay_task.h"

#include "detect_task.h"
#include "uart_device.h"
#include "keyboard.h"
#include "sys.h"


#define REL_CH1_ON   write_digital_io(DIGI_IO1, 0);
#define REL_CH1_OFF   write_digital_io(DIGI_IO1, 1);
#define REL_CH2_ON   write_digital_io(DIGI_IO2, 0);
#define REL_CH2_OFF   write_digital_io(DIGI_IO2, 1);
#define REL_CH3_ON   write_digital_io(DIGI_IO3, 0);
#define REL_CH3_OFF   write_digital_io(DIGI_IO3, 1);
#define REL_CH4_ON   write_digital_io(DIGI_IO4, 0);
#define REL_CH4_OFF   write_digital_io(DIGI_IO4, 1);

 

void relay_task(const void* argu){
	set_digital_io_dir(DIGI_IO1,IO_OUTPUT);
	set_digital_io_dir(DIGI_IO2,IO_OUTPUT);
	set_digital_io_dir(DIGI_IO3,IO_OUTPUT);
	set_digital_io_dir(DIGI_IO4,IO_OUTPUT);
	REL_CH1_OFF;
	REL_CH2_OFF;
	REL_CH3_OFF;
	REL_CH4_OFF;
	while(1){
		/*
		REL_CH1_ON;
		osDelay(200);
		REL_CH1_OFF;
		//osDelay(200);
		REL_CH2_ON;
		osDelay(200);
		REL_CH2_OFF;
		//osDelay(200);
		REL_CH3_ON;
		osDelay(200);
		REL_CH3_OFF;
		//osDelay(200);
		REL_CH4_ON;
		osDelay(200);
		REL_CH4_OFF;
		osDelay(500);*/
		
		switch (rc.sw1)
  {
    case RC_UP:{
		REL_CH1_ON;
		REL_CH2_ON;
		} //user custom function
   break;
    
   case RC_MI: {
	 	REL_CH2_OFF;
		REL_CH1_ON;
	 }//user custom function
    break;

    case RC_DN:
    {
		REL_CH1_OFF;
		REL_CH2_OFF;
    }
    break;
  }
			switch (rc.sw2)
  {
    case RC_UP:{
		REL_CH3_ON;
		REL_CH4_ON;
		} //user custom function
   break;
    
   case RC_MI: {
	 	REL_CH4_OFF;
		REL_CH3_ON;
	 }//user custom function
    break;

    case RC_DN:
    {
		REL_CH3_OFF;
		REL_CH4_OFF;
    }
    break;
  }
	
	}
}