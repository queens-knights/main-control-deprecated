#include "can1.h"
#include "stm32f4xx.h"
#include "pid.h"
#include "value_allinit.h"
#include "remote_task.h"
#include "motor_pid_task.h"
#include "detect_task.h"
#include "supply_task.h"
#include "digital_display.h"


#define PIDcalc_start 1500
#define No_Display_bit 10
void Loop();












