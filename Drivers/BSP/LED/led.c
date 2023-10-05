/**
 ****************************************************************************************************
 * @file        led.c
 * @author      正点原子团队(ALIENTEK)
 * @version     V1.0
 * @date        2021-10-14
 * @brief       LED 驱动代码
 * @license     Copyright (c) 2020-2032, 广州市星翼电子科技有限公司
 ****************************************************************************************************
 * @attention
 *
 * 实验平台:正点原子 探索者 F407开发板
 * 在线视频:www.yuanzige.com
 * 技术论坛:www.openedv.com
 * 公司网址:www.alientek.com
 * 购买地址:openedv.taobao.com
 *
 * 修改说明
 * V1.0 20211014
 * 第一次发布
 *
 ****************************************************************************************************
 */
 
#include "./BSP/LED/led.h"
#include "./SYSTEM/delay/delay.h"

/**
 * @brief       初始化LED相关IO口, 并使能时钟
 * @param       无
 * @retval      无
 */
void led_init(void)
{
    GPIO_InitTypeDef gpio_init_struct;
    
    LED0_GPIO_CLK_ENABLE();                                 /* LED0时钟使能 */
    LED1_GPIO_CLK_ENABLE();                                 /* LED1时钟使能 */

    gpio_init_struct.Pin = LED0_GPIO_PIN;                   /* LED0引脚 */
    gpio_init_struct.Mode = GPIO_MODE_OUTPUT_PP;            /* 推挽输出 */
    gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
    gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */
    HAL_GPIO_Init(LED0_GPIO_PORT, &gpio_init_struct);       /* 初始化LED0引脚 */

    gpio_init_struct.Pin = LED1_GPIO_PIN;                   /* LED1引脚 */
    HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);       /* 初始化LED1引脚 */
	
		gpio_init_struct.Pin =GPIO_PIN_9;
		HAL_GPIO_Init(LED1_GPIO_PORT, &gpio_init_struct);
    HAL_GPIO_WritePin(LED1_GPIO_PORT, GPIO_PIN_9, GPIO_PIN_SET);
	
    LED0(1);                                                /* 关闭 LED0 */
    LED1(1);                                                /* 关闭 LED1 */
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