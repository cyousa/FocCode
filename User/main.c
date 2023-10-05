/**
 ****************************************************************************************************
 * @file        main.c
 * @author      Chino
 * @version     V1.0
 * @date        2023-8-10
 * @brief       FOC
 * @license     Copyright (c) 2020-2032, �ӱ����̴�ѧ
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 ****************************************************************************************************
 */

#include "./SYSTEM/sys/sys.h"
#include "./SYSTEM/usart/usart.h"
#include "./SYSTEM/delay/delay.h"
#include "./BSP/LED/led.h"
#include "./BSP/PWM//pwm.h"
#include "./BSP/INTERUPT/interupt.h"
#include "./BSP/FOCCODE//foc_code.h"
#include "BSP/ENCONDER/enconder.h"
#include <math.h>
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_interface.h"
#include "./MALLOC/malloc.h"
#include "./BSP/ADC_I//adc.h"

extern float PWM_A,PWM_B,PWM_C;

extern TIM_HandleTypeDef timx_pwm_init;
extern ADC_HandleTypeDef hadc1;

extern float I_ref_ahp,I_ref_beta;
extern float Id_ref ,Iq_ref,Iq_avarge,Uq;

extern int time_speed;

extern float ta,tb,tc;
extern short enonder_old;
extern uint8_t dir;
extern float speed;
unsigned char tail[4]={0x00,0x00,0x80,0x7f};

uint16_t ADC_DMA_data[60];
extern float Ic,Ib,Ia;
extern float Aangle_Now;
USBD_HandleTypeDef USBD_Device;
extern 	float now_speed,speed_out;
uint8_t key_pre;
uint8_t current_add;
extern float current_target_uq,ud_target,angle,Vbus,Uq_current_error;
uint8_t isready = 0;
uint8_t clear_cnt=0;
int main()
{
		
    HAL_Init();                                 /* ��ʼ��HAL�� */
    sys_stm32_clock_init(336, 8, 2, 7);         /* ����ʱ��,168Mhz */
    delay_init(168);                            /* ��ʱ��ʼ�� */
		usart_init(115200); 
    led_init();                                 /* ��ʼ��LED */
		Timx_PWM_init(8400-1,1-1);//��ʱ�����PWM��ʼ��20khz
		TIM_Interupt_init(42000-1);//1ms�ж�500hz
		Enconder_init();//��������ʼ��
	
	  USBD_Init(&USBD_Device, &VCP_Desc, 0);                      /* ��ʼ��USB */
    USBD_RegisterClass(&USBD_Device, USBD_CDC_CLASS);           /* ����� */
    USBD_CDC_RegisterInterface(&USBD_Device, &USBD_CDC_fops);   /* ΪMSC����ӻص����� */
    USBD_Start(&USBD_Device);  
		MX_DMA_Init();
		MX_ADC1_Init();
		KEY_Init();
		HAL_ADC_Start_DMA(&hadc1,(uint32_t*)ADC_DMA_data,60);
		//SCB->CPACR|=8<<20;
		SystemInit();//����FPU ��������������
	//��5sһȦ ��ôһ���жϾ͵���0.02512rad  0.02512*250=6.28 һ�ܣ�������Ҫ�õ���Ƕȣ�����X7*/
	
	int8_t uq = 6;
    while(1)
    {
       // LED0(0);                                /* LED0 �� */
			//	LED1(1);                                /* LED1 �� */
      //  delay_ms(100);
        LED0(1);                                  /* LED0 �� */
       // LED1(0);                                /* LED1 �� */
       // delay_ms(100);
			
		key_pre=key_read();
			if(key_pre==1&&current_add==0)
			{
			
				current_add=1;
			}
			else if(key_pre==0&&current_add==1)
			{
				isready = 1;
				if(clear_cnt==0)
				{
				clear_cnt=1;
				TIM1->CNT = 0;
				}
				current_target_uq-=0.5f;
				ud_target=0;
				current_add=0;
			}
			
			////////
			if(key_pre==2&&current_add==0)
			{
			
				current_add=2;
			}
			else if(key_pre==0&&current_add==2)
			{
				current_target_uq+=0.5f;
				current_add=0;
			}
			
			
			usb_printf("%f,%f,%f,%f,%f\n",Ib,Ic,Ia,Iq_ref,Uq_current_error);
			

		
	

    }
}


