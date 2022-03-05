//=============================================================================
// DAC Configuration
// Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "dac.h"
#include "dma.h"
#include "Audio.h"

static int Audio_ErrorHandler( int const Status, bool const ShowOK );

static uint16_t dacBuf[4096];
static uint32_t dacBufSize = sizeof(dacBuf) / sizeof(uint16_t);

//-----------------------------------------------------------------------------
//! \brief Initialize Audio
//! \return Returns -1 in event of an Error, and 1 otherwise.
//-----------------------------------------------------------------------------
//int Audio_Init(void)
//{
//  return 1;
//}

//-----------------------------------------------------------------------------
//! \brief Generate a SawTooth waveform using DAC and DMA peripherals.
//! \param[in] FundamentalFrequency  Fundamental Frequency of waveform
//! \return Returns -1 in event of an Error, and 1 otherwise.
//-----------------------------------------------------------------------------
int Audio_DMA_SawTooth( uint32_t const FundamentalFrequency )
{
  bool              const ShowOK             = true;
  uint32_t          const SamplingFrequency  = DAC_GetSamplingFrequency();
  uint32_t          const NumSamplesInPeriod = SamplingFrequency / FundamentalFrequency;
  if( NumSamplesInPeriod > dacBufSize ) return Audio_ErrorHandler(-1, ShowOK);
  for( uint32_t n=0; n<NumSamplesInPeriod; n++ )
    dacBuf[n] = (0x0FFF * n) / (NumSamplesInPeriod-1);
  HAL_StatusTypeDef const Status1   = DAC_Start( );
  HAL_StatusTypeDef const Status2   = DAC_DMA_Start( (uint32_t*)dacBuf, NumSamplesInPeriod );
  int const Status = ( Status1==HAL_OK && Status2==HAL_OK )?  1 : -1;
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief Generate a Triangle waveform using DAC and DMA peripherals.
//! \param[in] FundamentalFrequency  Fundamental Frequency of waveform
//! \return Returns -1 in event of an Error, and 1 otherwise.
//-----------------------------------------------------------------------------
int Audio_DMA_Triangle( uint32_t const FundamentalFrequency )
{
  uint32_t n;
  bool              const ShowOK             = true;
  uint32_t          const SamplingFrequency  = DAC_GetSamplingFrequency();
  uint32_t          const NumSamplesInPeriod = SamplingFrequency / FundamentalFrequency;
  if( NumSamplesInPeriod > dacBufSize ) return Audio_ErrorHandler( -1, ShowOK );
  for( n=0; n<NumSamplesInPeriod/2; n++ ) dacBuf[n] = 0x0000          + (0x0FFF * n) / (NumSamplesInPeriod/2 - 1 );
  for(    ; n<NumSamplesInPeriod  ; n++ ) dacBuf[n] = 0x0FFF + 0x0FFF - (0x0FFF * n) / (NumSamplesInPeriod/2 - 0 );
//printf( "NumSamplesInPeriod = %ld\r\n", NumSamplesInPeriod );
//for( n=NumSamplesInPeriod/2-10; n<NumSamplesInPeriod/2+10; n++ ) printf("dacBuf[%ld] = 0x%04X = %d \r\n", n, dacBuf[n], dacBuf[n] );
  HAL_StatusTypeDef const Status1   = DAC_Start( );
  HAL_StatusTypeDef const Status2   = DAC_DMA_Start( (uint32_t*)dacBuf, NumSamplesInPeriod );
  Audio_ErrorHandler( Status1, ShowOK );
  Audio_ErrorHandler( Status2, ShowOK );
  int const Status = ( Status1==HAL_OK && Status2==HAL_OK )?  1 : -1;
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief Generate a Square waveform using DAC and DMA peripherals.
//! \param[in] FundamentalFrequency  Fundamental Frequency of waveform
//! \return Returns -1 in event of an Error, and 1 otherwise.
//-----------------------------------------------------------------------------
int Audio_DMA_Square( uint32_t const FundamentalFrequency )
{
  uint32_t n;
  bool              const ShowOK             = true;
  uint32_t          const SamplingFrequency  = DAC_GetSamplingFrequency();
  uint32_t          const NumSamplesInPeriod = SamplingFrequency / FundamentalFrequency;
  if( NumSamplesInPeriod > dacBufSize ) return Audio_ErrorHandler( -1, ShowOK );
  for( n=0; n<NumSamplesInPeriod/2; n++ ) dacBuf[n] = 0x0000;
  for(    ; n<NumSamplesInPeriod  ; n++ ) dacBuf[n] = 0x0FFF;
  HAL_StatusTypeDef const Status1   = DAC_Start( );
  HAL_StatusTypeDef const Status2   = DAC_DMA_Start( (uint32_t*)dacBuf, NumSamplesInPeriod );
  Audio_ErrorHandler( Status1, ShowOK );
  Audio_ErrorHandler( Status2, ShowOK );
  int const Status = ( Status1==HAL_OK && Status2==HAL_OK )?  1 : -1;
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief Generate a Triangle waveform using DAC and DMA peripherals.
//! \param[in] FundamentalFrequency  Fundamental Frequency of waveform
//! \return Returns -1 in event of an Error, and 1 otherwise.
//-----------------------------------------------------------------------------
static int Audio_ErrorHandler( int const Status, bool const ShowOK )
{
  if( Status<0 )
  {
    printf("Audio Error\r\n");
  }
  return Status;
}