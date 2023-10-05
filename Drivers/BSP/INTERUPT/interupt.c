#include"interupt.h"
#include "./BSP/FOCCODE//foc_code.h"
#include "BSP/ENCONDER/enconder.h"
#include "math.h"
short encoder_count;
short enonder_old;
uint8_t dir;
float speed;


int time_speed;

TIM_HandleTypeDef TIM_intrp={0};

void TIM_Interupt_init(uint32_t Time)
{
	
	TIM_intrp.Instance=TIM7;
	TIM_intrp.Init.CounterMode=TIM_COUNTERMODE_UP;
	TIM_intrp.Init.Prescaler=1;
	TIM_intrp.Init.Period=Time;
	
	HAL_TIM_Base_Init(&TIM_intrp);
	HAL_TIM_Base_Start_IT(&TIM_intrp);

}


void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance ==TIM7)
	{
	__HAL_RCC_TIM7_CLK_ENABLE();
	HAL_NVIC_SetPriority(TIM7_IRQn,0,0);
	HAL_NVIC_EnableIRQ(TIM7_IRQn);	
	}
	

}
void TIM7_IRQHandler(void)
{

	HAL_TIM_IRQHandler(&TIM_intrp);

}
int conuta=0;

uint8_t time_ms;
extern float speed_out;
extern float Aangle_Now;
float angle = 0;
extern uint8_t isready;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if(htim->Instance ==TIM7)
	{
		
		
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_5);
		if(isready){
			angle = (TIM1->CNT / 2048.f)*2*PI*7;
		}
		Aangle_Now = -angle;
		Aangle_Now = angle <= -2*PI ? 0 : angle;
		
		Park_change_Contrary();	
		sector_judg();//ÉÈÇøÅÐ¶Ï
		SVPWM();//SVPWM£»
		
		Current_sampling();
		Current_loop();


	}
	
}
 
