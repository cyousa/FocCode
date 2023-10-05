#include "pwm.h"

TIM_HandleTypeDef timx_pwm_init= {0};
TIM_OC_InitTypeDef PWM_Config= {0};



void Timx_PWM_init(uint32_t ARR,uint16_t psc)
{

	timx_pwm_init.Instance=TIMX_PWM;//定时器句柄，首地址（强转成结构体后的）
	timx_pwm_init.Init.Prescaler=psc;//预分配系数
	timx_pwm_init.Init.CounterMode=TIM_COUNTERMODE_CENTERALIGNED1;//计数模式
	timx_pwm_init.Init.Period=ARR;//重装载值
	HAL_TIM_PWM_Init(&timx_pwm_init);//配置定时器
	

	
	PWM_Config.OCMode=TIM_OCMODE_PWM2;//设置输出比较模式
	PWM_Config.Pulse=0;//比较值 初始化为0，后面动态调整
	PWM_Config.OCPolarity=TIM_OCPOLARITY_HIGH;//因为是PWM1模式，所以设置为低电平有效
	HAL_TIM_PWM_ConfigChannel(&timx_pwm_init,&PWM_Config,TIM_CHANNEL_1);//配置输出模式
	HAL_TIM_PWM_ConfigChannel(&timx_pwm_init,&PWM_Config,TIM_CHANNEL_2);//配置输出模式
	HAL_TIM_PWM_ConfigChannel(&timx_pwm_init,&PWM_Config,TIM_CHANNEL_3);//配置输出模式
	
	HAL_TIM_PWM_Start(&timx_pwm_init,TIM_CHANNEL_1);//使能比较输出
	HAL_TIM_PWM_Start(&timx_pwm_init,TIM_CHANNEL_2);//使能比较输出
	HAL_TIM_PWM_Start(&timx_pwm_init,TIM_CHANNEL_3);//使能比较输出
	
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	
	if(htim->Instance ==TIMX_PWM)
	{
		GPIO_InitTypeDef gpio_init_struct;
	
				PWM_TIMX_CLK_ENABLE();//定时器时钟使能
																	
				PWM_GPIO_CLK_ENABLE();//gpio时钟使能

				gpio_init_struct.Pin = PWM_GPIO_Pin;                 
				gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* 推挽输出 */
				gpio_init_struct.Pull = GPIO_PULLUP;                    /* 上拉 */
				gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */		
				gpio_init_struct.Alternate=PWM_GPIO_AF_TIMx;//复用功能一定要设置
				HAL_GPIO_Init(PWM_GPIO_Port, &gpio_init_struct);       /* 初始化引脚 */
		
				gpio_init_struct.Pin = GPIO_PIN_7;          
				HAL_GPIO_Init(PWM_GPIO_Port, &gpio_init_struct);       /* 初始化引脚 */
		
				gpio_init_struct.Pin = GPIO_PIN_8;          
				HAL_GPIO_Init(PWM_GPIO_Port, &gpio_init_struct);       /* 初始化引脚 */
		
	

	}

}

/*
	设置占空比 0-10000 A B C相
	example PWM_SetDuty_A(5000);
*/


void PWM_SetDuty_A(uint16_t duty)
{
				__HAL_TIM_SET_COMPARE(&timx_pwm_init,TIM_CHANNEL_1,duty);

	
}	
void PWM_SetDuty_B(uint16_t duty)
{

				__HAL_TIM_SET_COMPARE(&timx_pwm_init,TIM_CHANNEL_2,duty);

	
}	
void PWM_SetDuty_C(uint16_t duty)
{

				__HAL_TIM_SET_COMPARE(&timx_pwm_init,TIM_CHANNEL_3,duty);
	
}	

