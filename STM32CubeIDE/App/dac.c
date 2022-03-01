//=============================================================================
// DAC Configuration
// Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include "main.h"
#include "dac.h"
static void DAC_ErrorHandler( void );
extern DAC_HandleTypeDef hdac1;

//-----------------------------------------------------------------------------
//! \brief Configure Memory-to-DAC DMA stream
//! \param[in] hdac Pointer to DAC handle
//! \param[in] hdma Pointer to DMA handle
//-----------------------------------------------------------------------------
void DAC_Init(void)
{
  DAC_ChannelConfTypeDef sConfig = {0};
  hdac1.Instance = DAC1;
  if (HAL_DAC_Init(&hdac1) != HAL_OK)
  {
    Error_Handler();
  }
  /** DAC channel OUT1 config */
  sConfig.DAC_SampleAndHold  = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger        = DAC_TRIGGER_T6_TRGO;
  sConfig.DAC_OutputBuffer   = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
  sConfig.DAC_UserTrimming   = DAC_TRIMMING_FACTORY;

  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_1) != HAL_OK)
    DAC_ErrorHandler();
  if (HAL_DAC_ConfigChannel(&hdac1, &sConfig, DAC_CHANNEL_2) != HAL_OK)
    DAC_ErrorHandler();
}

//-----------------------------------------------------------------------------
//! \brief Start DAC
//-----------------------------------------------------------------------------
void DAC_Start( void )
{
  DAC_HandleTypeDef * const Handle   = &hdac1; 
  uint32_t            const Channel1 = DAC_CHANNEL_1;
  uint32_t            const Channel2 = DAC_CHANNEL_2;
  
  HAL_DAC_Start( Handle, Channel1 );
  HAL_DAC_Start( Handle, Channel2 );
}

//-----------------------------------------------------------------------------
//! \brief Start DAC DMA transfers
//-----------------------------------------------------------------------------
void DAC_DMA_Start( uint32_t * const dacBuf, uint32_t const Length )
{
  DAC_HandleTypeDef * const Handle    = &hdac1; 
  uint32_t            const Channel1  = DAC_CHANNEL_1;
  uint32_t            const Channel2  = DAC_CHANNEL_2;
  uint32_t            const Alignment = DAC_ALIGN_12B_R;
  HAL_DAC_Start_DMA( Handle, Channel1, dacBuf, Length, Alignment );
  HAL_DAC_Start_DMA( Handle, Channel2, dacBuf, Length, Alignment );
}

//-----------------------------------------------------------------------------
//! \brief Configure Memory-to-DAC DMA stream
//! \param[in] hdac Pointer to DAC handle
//! \param[in] hdma Pointer to DMA handle
//-----------------------------------------------------------------------------
static void DAC_ErrorHandler( void )
{
  printf("DAC Error\r\n");
}

