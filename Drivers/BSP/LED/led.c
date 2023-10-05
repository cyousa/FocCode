/**
 ****************************************************************************************************
 * @file        led.c
 * @author      ����ԭ���Ŷ�(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-14
 * @brief       LED ��������
 * @license     Copyright (c) 2020-2032, ������������ӿƼ����޹�˾
 ****************************************************************************************************
 * @attention
 *
 * ʵ��ƽ̨:����ԭ�� ̽���� F407������
 * ������Ƶ:www.yuanzige.com
 * ������̳:www.openedv.com
 * ��˾��ַ:www.alientek.com
 * �����ַ:openedv.taobao.com
 *
 * �޸�˵��
 * V1.0 20211014
 * ��һ�η���
 *
 ****************************************************************************************************
 */
 
#include "./BSP/LED/led.h"
#include "./SYSTEM/delay/delay.h"

/**
 * @brief       ��ʼ��LED���IO��, ��ʹ��ʱ��
 * @param       ��
 * @retval      ��
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    LED0_GPIO_CLK_ENABLE();                                 /* LED0ʱ��ʹ�� */
    LED1_GPIO_CLK_ENABLE();                                 /* LED1ʱ��ʹ�� */

    gpio_init_struct.Pin = LED0_GPIO_PIN;                   /* LED0���� */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* ������� */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */
    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED0���� */

    gpio_init_struct.Pin = LED1_GPIO_PIN;                   /* LED1���� */
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);       /* ��ʼ��LED1���� */
	
		gpio_init_struct.Pin =GPIO_PIN_9;
		HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);
    HAL_GPIO_WritePin(LED1_GPIO_PORT, GPIO_PIN_9, GPIO_PIN_SET);
	
    LED0(1);                                                /* �ر� LED0 */
    LED1(1);                                                /* �ر� LED1 */
}
void KEY_Init()
{
	  GPIO_InitTypeDef key_init = {0};
	    __HAL_RCC_GPIOB_CLK_ENABLE();
    /**ADC1 GPIO Configuration
    PA1     ------> ADC1_IN1
    PA2     ------> ADC1_IN2
    PB0     ------> ADC1_IN8
    */
    key_init.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
    key_init.Mode = GPIO_MODE_INPUT;
    key_init.Pull = GPIO_PULLDOWN;
		key_init.Speed=GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &key_init);

	



}

uint8_t key_read()
{

		uint8_t key_num;
	if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0)
	{
		delay_ms(1);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5)==0)
		{
		key_num=1;
		}
		
		
	}
	else if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)==0)
	{
	
				delay_ms(1);
		if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_6)==0)
		{
		key_num=2;
		}
	}
	else
	{
		key_num=0;
	}
	
		
	return key_num;
}
void key_scan()
{


}