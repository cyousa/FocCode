#ifndef __PWM_H
#define __PWM_H

#include "./SYSTEM/sys/sys.h"


void Timx_PWM_init(uint32_t ARR,uint16_t psc);


#define TIMX_PWM  TIM8									//输出PWM的定时器
#define PWM_GPIO_Pin  GPIO_PIN_6
#define PWM_GPIO_Port  GPIOC            //配置引脚Port
#define PWM_GPIO_AF_TIMx GPIO_AF3_TIM8  //复用功能

#define	PWM_TIMX_CLK_ENABLE()      do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)  /* TIM8 时钟使能 */

#define PWM_GPIO_CLK_ENABLE() do{  __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)  /* PF口时钟使能 */

#define PWM_Max   10000  //最大占空比

void PWM_SetDuty_A(uint16_t duty);
void PWM_SetDuty_B(uint16_t duty);
void PWM_SetDuty_C(uint16_t duty);


#endif