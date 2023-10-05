#ifndef __FOC_CODE_H
#define __FOC_CODE_H

#include "./SYSTEM/sys/sys.h"
#include "./BSP/PWM/pwm.h"
#include "./CMSIS/DSP/Include/arm_math.h"

#define angel_Elc_MAX  6.28f


#define V_power 12.6f
#define squrt3 1.73205f
#define N 10  

float angel_normal(float angel);
float PWM_out_normal(float pwm);
void Park_change(float Ia,float Ib,float angel);
void Klark_change(float Ia,float Ib,float Ic);
void Park_change_Contrary();
void Klark_change_Contrary();
void sector_judg();
void SVPWM();
void Low_pass_filtering();
void Current_sampling();
void Current_loop();
void Position_loop();
void Speed_loop();
#endif