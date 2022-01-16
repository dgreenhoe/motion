//=============================================================================
// DMA configuration
// Daniel J. Greenhoe
// Reference: https://www.eevblog.com/forum/microcontrollers/stm32f407vge-dac-using-dma/
//=============================================================================
#include "main.h"
void DMA_Config(DAC_HandleTypeDef *hdac, DMA_HandleTypeDef *hdma)
{
  __HAL_RCC_DMA1_CLK_ENABLE();

  hdma->Instance                  = DMA1_Stream0;

  hdma->Init.Direction            = DMA_MEMORY_TO_PERIPH;
  hdma->Init.PeriphInc            = DMA_PINC_DISABLE;
  hdma->Init.MemInc               = DMA_MINC_ENABLE;
  hdma->Init.PeriphDataAlignment  = DMA_PDATAALIGN_WORD;
  hdma->Init.MemDataAlignment     = DMA_MDATAALIGN_WORD;
  hdma->Init.Mode                 = DMA_CIRCULAR;
  hdma->Init.Priority             = DMA_PRIORITY_VERY_HIGH;
  hdma->Init.FIFOMode             = DMA_FIFOMODE_ENABLE;
  hdma->Init.FIFOThreshold        = DMA_FIFO_THRESHOLD_1QUARTERFULL;
  hdma->Init.MemBurst             = DMA_MBURST_SINGLE;
  hdma->Init.PeriphBurst          = DMA_PBURST_SINGLE;

  HAL_DMA_Init(hdma);
}