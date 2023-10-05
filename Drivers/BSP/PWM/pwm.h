#ifndef __PWM_H
#define __PWM_H

#include "./SYSTEM/sys/sys.h"


void Timx_PWM_init(uint32_t ARR,uint16_t psc);


#define TIMX_PWM  TIM8									//���PWM�Ķ�ʱ��
#define PWM_GPIO_Pin  GPIO_PIN_6
#define PWM_GPIO_Port  GPIOC            //��������Port
#define PWM_GPIO_AF_TIMx GPIO_AF3_TIM8  //���ù���

#define	PWM_TIMX_CLK_ENABLE()      do{ __HAL_RCC_TIM8_CLK_ENABLE(); }while(0)  /* TIM8 ʱ��ʹ�� */

#define PWM_GPIO_CLK_ENABLE() do{  __HAL_RCC_GPIOC_CLK_ENABLE(); }while(0)  /* PF��ʱ��ʹ�� */

#define PWM_Max   10000  //���ռ�ձ�

void PWM_SetDuty_A(uint16_t duty);
void PWM_SetDuty_B(uint16_t duty);
void PWM_SetDuty_C(uint16_t duty);


#endif