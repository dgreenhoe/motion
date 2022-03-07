//=============================================================================
// DMA configuration
// Daniel J. Greenhoe
// Reference: https://www.eevblog.com/forum/microcontrollers/stm32f407vge-dac-using-dma/
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "AppMain.h"
#include "dma.h"

extern DMA_HandleTypeDef hdma_dac1_ch1;
extern DMA_HandleTypeDef hdma_dac1_ch2;
static HAL_StatusTypeDef DMA_ErrorHandler( HAL_StatusTypeDef const Status, bool const ShowOK );

//-----------------------------------------------------------------------------
//! \brief Initialize DMA
//-----------------------------------------------------------------------------
void DMA_Init( void )
{
  IRQn_Type      const Stream0     = DMA1_Stream0_IRQn;
  IRQn_Type      const Stream1     = DMA1_Stream1_IRQn;
  uint32_t       const PrePriority = 0;
  uint32_t       const SubPriority = 0;
  __HAL_RCC_DMA1_CLK_ENABLE();
  HAL_NVIC_SetPriority( Stream0, PrePriority, SubPriority );
  HAL_NVIC_SetPriority( Stream1, PrePriority, SubPriority );
  HAL_NVIC_EnableIRQ(   Stream0 );
  HAL_NVIC_EnableIRQ(   Stream1 );
}

//-----------------------------------------------------------------------------
//! \brief Configure Memory-to-DAC DMA stream
//! \param[in] Normal 0 for Cicular DMA, 1 for Normal
//! \return Returns void
//-----------------------------------------------------------------------------
void DMA_Config( int const Normal )
{
  bool               const ShowOK    = false;
  DMA_HandleTypeDef* const Handle1   = &hdma_dac1_ch1;
  DMA_HandleTypeDef* const Handle2   = &hdma_dac1_ch2;
  void*              const Stream0   = DMA1_Stream0;
  void*              const Stream1   = DMA1_Stream1;
  DMA_HandleTypeDef*       Handle    = Handle1;
  void*                    Stream    = Stream0;
  uint32_t Mode;
  switch( Normal )
  {
    case 0  : Mode = DMA_CIRCULAR;                           break;
    case 1  : Mode = DMA_NORMAL  ;                           break;
    default : DMA_ErrorHandler( HAL_ERROR, ShowOK ); return; break;
  }

  for( int i=0; i<2; i++ )
  {
    Handle->Instance                  = Stream;
    Handle->Init.Direction            = DMA_MEMORY_TO_PERIPH;
    Handle->Init.PeriphInc            = DMA_PINC_DISABLE;
    Handle->Init.MemInc               = DMA_MINC_ENABLE;
    Handle->Init.PeriphDataAlignment  = DMA_PDATAALIGN_HALFWORD; // _BYTE, _HALFWORD, _WORD
    Handle->Init.MemDataAlignment     = DMA_MDATAALIGN_HALFWORD; // _BYTE, _HALFWORD, _WORD
    Handle->Init.Mode                 = Mode;                    // NORMAL, CIRCULAR, PFCTRL, DOUBLE_BUFFER_M0, DOUBLE_BUFFER_M1
    Handle->Init.Priority             = DMA_PRIORITY_VERY_HIGH;
    Handle->Init.FIFOMode             = DMA_FIFOMODE_ENABLE;
    Handle->Init.FIFOThreshold        = DMA_FIFO_THRESHOLD_1QUARTERFULL;
    Handle->Init.MemBurst             = DMA_MBURST_SINGLE;
    Handle->Init.PeriphBurst          = DMA_PBURST_SINGLE;
    HAL_DMA_Init( Handle );
    Handle = Handle2;
    Stream = Stream1;
  }

}

//-----------------------------------------------------------------------------
//! \brief DMA Error Handler
//! \param[in] Status HAL Status code
//! \param[in] ShowOK If ShowOK==true, display event Status=HAL_OK, otherwise hide this event.
//! \return Return Status
//-----------------------------------------------------------------------------
static HAL_StatusTypeDef DMA_ErrorHandler( HAL_StatusTypeDef const Status, bool const ShowOK )
{
  if( !ShowOK || Status!=HAL_OK )
  {
    printf("DMA " );
    Display_HAL_Status( Status, ShowOK );
  }
  return Status;
}