//=============================================================================
//! \file dac.c
//!       DAC Configuration
//! \author Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "AppMain.h"
#include "dac.h"
static HAL_StatusTypeDef DAC_ErrorHandler( HAL_StatusTypeDef const Status, bool const ShowOK );
extern DAC_HandleTypeDef hdac1;

//-----------------------------------------------------------------------------
//! \brief Get Sampling Frequency for DAC
//! \return Sampling Frequency in Hertz
//-----------------------------------------------------------------------------
uint32_t DAC_GetSamplingFrequency(void)
{
  uint32_t const SamplingFrequency = 44100;
  return SamplingFrequency;
}

//-----------------------------------------------------------------------------
//! \brief Configure Memory-to-DAC DMA stream
//! \param[in] hdac Pointer to DAC handle
//! \param[in] hdma Pointer to DMA handle
//! \return Return Status
//-----------------------------------------------------------------------------
HAL_StatusTypeDef DAC_Init(void)
{
  HAL_StatusTypeDef         Status    = HAL_OK;
  bool                const ShowOK    = true;
  DAC_HandleTypeDef * const Handle    = &hdac1; 
  uint32_t            const Channel1  = DAC_CHANNEL_1;
  uint32_t            const Channel2  = DAC_CHANNEL_2;
  uint32_t            const Alignment = DAC_ALIGN_12B_R;
  uint32_t            const InitialValue = 0x0800;

  Handle->Instance                    = DAC1;
  DAC_ChannelConfTypeDef   sConfig    = {0};
  sConfig.DAC_SampleAndHold           = DAC_SAMPLEANDHOLD_DISABLE;
  sConfig.DAC_Trigger                 = DAC_TRIGGER_T6_TRGO;
  sConfig.DAC_OutputBuffer            = DAC_OUTPUTBUFFER_ENABLE;
  sConfig.DAC_ConnectOnChipPeripheral = DAC_CHIPCONNECT_DISABLE;
  sConfig.DAC_UserTrimming            = DAC_TRIMMING_FACTORY;
  HAL_StatusTypeDef   const Status1   = HAL_DAC_Init( Handle );
  HAL_StatusTypeDef   const Status2   = HAL_DAC_ConfigChannel( Handle, &sConfig, Channel1 );
  HAL_StatusTypeDef   const Status3   = HAL_DAC_ConfigChannel( Handle, &sConfig, Channel2 );
  HAL_StatusTypeDef   const Status4   = HAL_DAC_SetValue(      Handle, Channel1, Alignment, InitialValue  );
  HAL_StatusTypeDef   const Status5   = HAL_DAC_SetValue(      Handle, Channel2, Alignment, InitialValue  );

  DAC_ErrorHandler( Status1, ShowOK );
  DAC_ErrorHandler( Status2, ShowOK );
  DAC_ErrorHandler( Status3, ShowOK );
  if( Status3 != HAL_OK )   Status    = Status3;
  if( Status2 != HAL_OK )   Status    = Status2;
  if( Status1 != HAL_OK )   Status    = Status1;
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief  Start DAC
//! \return Return Status
//-----------------------------------------------------------------------------
HAL_StatusTypeDef DAC_Start( void )
{
  HAL_StatusTypeDef         Status       = HAL_OK;
  bool                const ShowOK       = true;
  DAC_HandleTypeDef * const Handle       = &hdac1; 
  uint32_t            const Channel1     = DAC_CHANNEL_1;
  uint32_t            const Channel2     = DAC_CHANNEL_2;
  uint32_t            const Alignment    = DAC_ALIGN_12B_R;
  uint32_t            const InitialValue = 0x0800;

  HAL_StatusTypeDef   const Status1      = HAL_DAC_Start(     Handle, Channel1 );
  HAL_StatusTypeDef   const Status2      = HAL_DAC_Start(     Handle, Channel2 );
  HAL_StatusTypeDef   const Status3      = HAL_DAC_SetValue( Handle, Channel1, Alignment, InitialValue  );
  HAL_StatusTypeDef   const Status4      = HAL_DAC_SetValue( Handle, Channel2, Alignment, InitialValue  );
  DAC_ErrorHandler( Status1, ShowOK );
  DAC_ErrorHandler( Status2, ShowOK );
  DAC_ErrorHandler( Status3, ShowOK );
  DAC_ErrorHandler( Status4, ShowOK );
  if( Status4 != HAL_OK )   Status       = Status4;
  if( Status3 != HAL_OK )   Status       = Status3;
  if( Status2 != HAL_OK )   Status       = Status2;
  if( Status1 != HAL_OK )   Status       = Status1;
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief Set DAC Value
//! \return Return Status
//-----------------------------------------------------------------------------
HAL_StatusTypeDef DAC_SetValue( uint32_t const DataValue )
{
  bool                const ShowOK    = true;
  DAC_HandleTypeDef * const Handle    = &hdac1; 
  uint32_t            const Channel1  = DAC_CHANNEL_1;
  uint32_t            const Channel2  = DAC_CHANNEL_2;
  uint32_t            const Alignment = DAC_ALIGN_12B_R;

  HAL_StatusTypeDef   const Status1   = HAL_DAC_SetValue( Handle, Channel1, Alignment, DataValue  );
  HAL_StatusTypeDef   const Status2   = HAL_DAC_SetValue( Handle, Channel2, Alignment, DataValue  );
  DAC_ErrorHandler( Status1, ShowOK );
  DAC_ErrorHandler( Status2, ShowOK );
  return Status1!=HAL_OK? Status1 : Status2;
}

//-----------------------------------------------------------------------------
//! \brief Start DAC
//! \return Return Status
//-----------------------------------------------------------------------------
HAL_StatusTypeDef DAC_Stop( void )
{
  HAL_StatusTypeDef         Status   = HAL_OK;
  bool                const ShowOK   = true;
  DAC_HandleTypeDef * const Handle   = &hdac1; 
  uint32_t            const Channel1 = DAC_CHANNEL_1;
  uint32_t            const Channel2 = DAC_CHANNEL_2;
  HAL_StatusTypeDef   const Status1  = HAL_DAC_Stop_DMA( Handle, Channel1 );
  HAL_StatusTypeDef   const Status2  = HAL_DAC_Stop_DMA( Handle, Channel2 );
  HAL_StatusTypeDef   const Status3  = HAL_DAC_Stop(     Handle, Channel1 );
  HAL_StatusTypeDef   const Status4  = HAL_DAC_Stop(     Handle, Channel2 );
  DAC_ErrorHandler( Status1, ShowOK );
  DAC_ErrorHandler( Status2, ShowOK );
  DAC_ErrorHandler( Status3, ShowOK );
  DAC_ErrorHandler( Status4, ShowOK );
  if ( Status4 != HAL_OK )  Status   = Status4;
  if ( Status3 != HAL_OK )  Status   = Status3;
  if ( Status2 != HAL_OK )  Status   = Status2;
  if ( Status1 != HAL_OK )  Status   = Status1;
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief Start DAC DMA transfers
//! \param[in] dacBuf   Pointer to DAC buffer
//! \param[in] Length   Number of valid elements in buffer
//! \return Return Status
//-----------------------------------------------------------------------------
HAL_StatusTypeDef DAC_DMA_Start( uint32_t * const dacBuf, uint32_t const Length )
{
  bool                const ShowOK    = true;
  DAC_HandleTypeDef * const Handle    = &hdac1; 
  uint32_t            const Channel1  = DAC_CHANNEL_1;
  uint32_t            const Channel2  = DAC_CHANNEL_2;
  uint32_t            const Alignment = DAC_ALIGN_12B_R;
  HAL_StatusTypeDef   const Status1   = HAL_DAC_Start_DMA( Handle, Channel1, dacBuf, Length, Alignment );
  HAL_StatusTypeDef   const Status2   = HAL_DAC_Start_DMA( Handle, Channel2, dacBuf, Length, Alignment );
  DAC_ErrorHandler( Status1, ShowOK );
  DAC_ErrorHandler( Status2, ShowOK );
  return Status1!=HAL_OK? Status1 : Status2;
}

//-----------------------------------------------------------------------------
//! \brief DAC Error Handler
//! \param[in] Status HAL Status code
//! \param[in] ShowOK If ShowOK==true, display event Status=HAL_OK, otherwise hide this event.
//! \return Return Status
//-----------------------------------------------------------------------------
static HAL_StatusTypeDef DAC_ErrorHandler( HAL_StatusTypeDef const Status, bool const ShowOK )
{
  if( !ShowOK || Status!=HAL_OK )
  {
    printf("DAC " );
    Display_HAL_Status( Status, ShowOK );
  }
  return Status;
}