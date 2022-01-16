//=============================================================================
// DMA configuration
// Daniel J. Greenhoe
// Reference: https://www.eevblog.com/forum/microcontrollers/stm32f407vge-dac-using-dma/
//=============================================================================
#include "main.h"

//-----------------------------------------------------------------------------
// \brief Configure Memory-to-DAC DMA stream
// \param[in] hdac Pointer to DAC handle
// \param[in] hdma Pointer to DMA handle
//-----------------------------------------------------------------------------
void DMA_Config(const DAC_HandleTypeDef *hdac, DMA_HandleTypeDef *hdma, void * Stream)
{
  hdma->Instance                  = Stream;

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