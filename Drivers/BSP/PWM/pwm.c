#include "pwm.h"

TIM_HandleTypeDef timx_pwm_init= {0};
TIM_OC_InitTypeDef PWM_Config= {0};



void Timx_PWM_init(uint32_t ARR,uint16_t psc)
{

	timx_pwm_init.Instance=TIMX_PWM;//��ʱ��������׵�ַ��ǿת�ɽṹ���ģ�
	timx_pwm_init.Init.Prescaler=psc;//Ԥ����ϵ��
	timx_pwm_init.Init.CounterMode=TIM_COUNTERMODE_CENTERALIGNED1;//����ģʽ
	timx_pwm_init.Init.Period=ARR;//��װ��ֵ
	HAL_TIM_PWM_Init(&timx_pwm_init);//���ö�ʱ��
	

	
	PWM_Config.OCMode=TIM_OCMODE_PWM2;//��������Ƚ�ģʽ
	PWM_Config.Pulse=0;//�Ƚ�ֵ ��ʼ��Ϊ0�����涯̬����
	PWM_Config.OCPolarity=TIM_OCPOLARITY_HIGH;//��Ϊ��PWM1ģʽ����������Ϊ�͵�ƽ��Ч
	HAL_TIM_PWM_ConfigChannel(&timx_pwm_init,&PWM_Config,TIM_CHANNEL_1);//�������ģʽ
	HAL_TIM_PWM_ConfigChannel(&timx_pwm_init,&PWM_Config,TIM_CHANNEL_2);//�������ģʽ
	HAL_TIM_PWM_ConfigChannel(&timx_pwm_init,&PWM_Config,TIM_CHANNEL_3);//�������ģʽ
	
	HAL_TIM_PWM_Start(&timx_pwm_init,TIM_CHANNEL_1);//ʹ�ܱȽ����
	HAL_TIM_PWM_Start(&timx_pwm_init,TIM_CHANNEL_2);//ʹ�ܱȽ����
	HAL_TIM_PWM_Start(&timx_pwm_init,TIM_CHANNEL_3);//ʹ�ܱȽ����
	
}

void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	
	if(htim->Instance ==TIMX_PWM)
	{
		GPIO_InitTypeDef gpio_init_struct;
	
				PWM_TIMX_CLK_ENABLE();//��ʱ��ʱ��ʹ��
																	
				PWM_GPIO_CLK_ENABLE();//gpioʱ��ʹ��

				gpio_init_struct.Pin = PWM_GPIO_Pin;                 
				gpio_init_struct.Mode = GPIO_MODE_AF_PP;            /* ������� */
				gpio_init_struct.Pull = GPIO_PULLUP;                    /* ���� */
				gpio_init_struct.Speed = GPIO_SPEED_FREQ_HIGH;          /* ���� */		
				gpio_init_struct.Alternate=PWM_GPIO_AF_TIMx;//���ù���һ��Ҫ����
				HAL_GPIO_Init(PWM_GPIO_Port, &gpio_init_struct);       /* ��ʼ������ */
		
				gpio_init_struct.Pin = GPIO_PIN_7;          
				HAL_GPIO_Init(PWM_GPIO_Port, &gpio_init_struct);       /* ��ʼ������ */
		
				gpio_init_struct.Pin = GPIO_PIN_8;          
				HAL_GPIO_Init(PWM_GPIO_Port, &gpio_init_struct);       /* ��ʼ������ */
		
	

	}

}

/*
	����ռ�ձ� 0-10000 A B C��
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

