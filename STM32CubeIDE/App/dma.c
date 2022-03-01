//=============================================================================
// DMA configuration
// Daniel J. Greenhoe
// Reference: https://www.eevblog.com/forum/microcontrollers/stm32f407vge-dac-using-dma/
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "dma.h"

extern DMA_HandleTypeDef hdma_dac1_ch1;
extern DMA_HandleTypeDef hdma_dac1_ch2;

//-----------------------------------------------------------------------------
//! \brief Initialize DMA
//-----------------------------------------------------------------------------
void DMA_Init( void )
{
  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);
  /* DMA1_Stream1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);
}

//-----------------------------------------------------------------------------
//! \brief Configure Memory-to-DAC DMA stream
//! \param[in] hdma Pointer to DMA handle
//-----------------------------------------------------------------------------
void DMA_Config( DMA_HandleTypeDef *hdma, void * Stream )
{
  hdma->Instance                  = Stream;

  hdma->Init.Direction            = DMA_MEMORY_TO_PERIPH;
  hdma->Init.PeriphInc            = DMA_PINC_DISABLE;
  hdma->Init.MemInc               = DMA_MINC_ENABLE;
  hdma->Init.PeriphDataAlignment  = DMA_PDATAALIGN_HALFWORD; // _BYTE, _HALFWORD, _WORD
  hdma->Init.MemDataAlignment     = DMA_MDATAALIGN_HALFWORD; // _BYTE, _HALFWORD, _WORD
  hdma->Init.Mode                 = DMA_CIRCULAR;            // NORMAL, CIRCULAR, PFCTRL, DOUBLE_BUFFER_M0, DOUBLE_BUFFER_M1
  hdma->Init.Priority             = DMA_PRIORITY_VERY_HIGH;
  hdma->Init.FIFOMode             = DMA_FIFOMODE_ENABLE;
  hdma->Init.FIFOThreshold        = DMA_FIFO_THRESHOLD_1QUARTERFULL;
  hdma->Init.MemBurst             = DMA_MBURST_SINGLE;
  hdma->Init.PeriphBurst          = DMA_PBURST_SINGLE;

  HAL_DMA_Init(hdma);
}

