#include"enconder.h"

	TIM_HandleTypeDef TIM_Encoder_init;
	
  TIM_Encoder_InitTypeDef TIM_Encoder_config;
	
	TIM_SlaveConfigTypeDef TIM_SlaveConfig;
	
	TIM_MasterConfigTypeDef TIM_MasterConfig;
void Enconder_init()
{
			
	TIM_Encoder_init.Instance=TIM1;
	TIM_Encoder_init.Init.Period=2047;
	TIM_Encoder_init.Init.Prescaler=0;
	TIM_Encoder_init.Init.CounterMode=TIM_COUNTERMODE_UP;
	TIM_Encoder_init.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
	TIM_Encoder_init.Init.RepetitionCounter=0;
	TIM_Encoder_init.Init.AutoReloadPreload=TIM_AUTORELOAD_PRELOAD_DISABLE;

	TIM_Encoder_config.EncoderMode=TIM_ENCODERMODE_TI12;
	TIM_Encoder_config.IC1Filter=6;//关闭滤波器
	TIM_Encoder_config.IC1Polarity=TIM_INPUTCHANNELPOLARITY_RISING;	//上升沿计数 
	TIM_Encoder_config.IC1Prescaler=TIM_ICPSC_DIV1;//预分配，不分频
	TIM_Encoder_config.IC1Selection=TIM_ICSELECTION_DIRECTTI;//CC1 通道配置为输入，IC1 映射到 TI1 上
	
	TIM_Encoder_config.IC2Filter=6;//关闭滤波器
	TIM_Encoder_config.IC2Polarity=TIM_INPUTCHANNELPOLARITY_RISING;	//上升沿计数
	TIM_Encoder_config.IC2Prescaler=TIM_ICPSC_DIV1;//预分配，不分频
	TIM_Encoder_config.IC2Selection=TIM_ICSELECTION_DIRECTTI;//CC1 通道配置为输入，IC1 映射到 TI2 上

	HAL_TIM_Encoder_Init(&TIM_Encoder_init,&TIM_Encoder_config);
	
	HAL_TIM_Encoder_Start(&TIM_Encoder_init, TIM_CHANNEL_ALL);


	TIM_MasterConfig.MasterOutputTrigger=TIM_TRGO_RESET;
	TIM_MasterConfig.MasterSlaveMode=TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&TIM_Encoder_init,&TIM_MasterConfig);

}

void HAL_TIM_Encoder_MspInit(TIM_HandleTypeDef *htim)
{

		if(htim->Instance ==TIM1)
	{
				__HAL_RCC_TIM1_CLK_ENABLE();
				__HAL_RCC_GPIOA_CLK_ENABLE();
				GPIO_InitTypeDef gpio_init_struct;//相关引脚配置
	
				gpio_init_struct.Pin = GPIO_PIN_8;                 
				gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* 推挽输出 */
				gpio_init_struct.Pull = GPIO_PULLDOWN;                    /* 上拉 */
				gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* 高速 */		
				gpio_init_struct.Alternate=GPIO_AF1_TIM1;//复用功能一定要设置
				HAL_GPIO_Init(GPIOA, &gpio_init_struct);       /* 初始化引脚 */
				
				gpio_init_struct.Pin = GPIO_PIN_9;          
				HAL_GPIO_Init(GPIOA, &gpio_init_struct);       /* 初始化引脚 */		

	}

}