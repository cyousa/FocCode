#include "dma.h"

DMA_HandleTypeDef Dma_init;
void DMA_init()
{
		__HAL_RCC_DMA2_CLK_ENABLE();
		//Dma_init.Instance=ADC1;




}