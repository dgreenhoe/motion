//=============================================================================
// DAC Configuration
// Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include "main.h"
#include "dac.h"
#include "dma.h"
#include "Audio.h"
#include "AudioData.h"
static int Audio_ErrorHandler( int const Status, bool const ShowOK );

//static uint16_t dacBuf[200*1024-(85952/2)+1];
static uint16_t dacBuf[158*1024];
static uint32_t dacBufSize = sizeof(dacBuf) / sizeof(uint16_t);

//-----------------------------------------------------------------------------
//! \brief Initialize Audio
//! \return Returns -1 in event of an Error, and 1 otherwise.
//-----------------------------------------------------------------------------
int Audio_Init(void)
{
  bool              const ShowOK  = true;
  uint32_t const NumSamples = sizeof( AudioData ) / sizeof( uint16_t );
  if( NumSamples > dacBufSize ) return Audio_ErrorHandler(-1, ShowOK);
  for( uint32_t n=0; n<NumSamples; n++ )// Copy data from Flash to RAM
    dacBuf[n] = AudioData[n];
  HAL_StatusTypeDef const Status3   = DAC_Stop( );
  HAL_StatusTypeDef const Status1   = DAC_Start( );
  HAL_StatusTypeDef const Status2   = DAC_DMA_Start( (uint32_t*)dacBuf, NumSamples );
  Audio_ErrorHandler( Status1, ShowOK );
  Audio_ErrorHandler( Status2, ShowOK );
  Audio_ErrorHandler( Status3, ShowOK );
  int const Status = ( Status1==HAL_OK && Status2==HAL_OK )?  1 : -1;
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief Silence all audio.
//! \return Returns -1 in event of an Error, and 1 otherwise.
//-----------------------------------------------------------------------------
int Audio_Silence( void )
{
  bool              const ShowOK  = true;
  HAL_StatusTypeDef const Status1 = DAC_Stop( );
  int const Status = ( Status1==HAL_OK )?  1 : -1;
  Audio_ErrorHandler( Status, ShowOK );
  return Status;
}

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
  HAL_StatusTypeDef const Status3   = DAC_Stop( );
  HAL_StatusTypeDef const Status1   = DAC_Start( );
  DMA_Config( 0 );
  HAL_StatusTypeDef const Status2   = DAC_DMA_Start( (uint32_t*)dacBuf, NumSamplesInPeriod );
  Audio_ErrorHandler( Status1, ShowOK );
  Audio_ErrorHandler( Status2, ShowOK );
  Audio_ErrorHandler( Status3, ShowOK );
  int const Status = ( Status1==HAL_OK && Status2==HAL_OK )?  1 : -1;
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief Generate a Triangle waveform using DAC and DMA peripherals.
//! \param[in] FundamentalFrequency  Fundamental Frequency of waveform
//! \return Returns -1 in event of an Error, and 1 otherwise.
//-----------------------------------------------------------------------------
int Audio_DumpDACbuf( uint32_t const Start, uint32_t const NumSamples )
{
  printf( "NumSamples = %ld\r\n", NumSamples );
  for( uint32_t n=Start; n<NumSamples; n++ ) 
    printf("dacBuf[%ld] = 0x%04X = %d \r\n", n, dacBuf[n], dacBuf[n] );
  return 1;
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
  HAL_StatusTypeDef const Status3   = DAC_Stop( );
  HAL_StatusTypeDef const Status1   = DAC_Start( );
  DMA_Config( 0 );
  HAL_StatusTypeDef const Status2   = DAC_DMA_Start( (uint32_t*)dacBuf, NumSamplesInPeriod );
  Audio_ErrorHandler( Status1, ShowOK );
  Audio_ErrorHandler( Status2, ShowOK );
  Audio_ErrorHandler( Status3, ShowOK );
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
  HAL_StatusTypeDef const Status3   = DAC_Stop( );
  HAL_StatusTypeDef const Status1   = DAC_Start( );
  DMA_Config( 0 );
  HAL_StatusTypeDef const Status2   = DAC_DMA_Start( (uint32_t*)dacBuf, NumSamplesInPeriod );
  Audio_ErrorHandler( Status1, ShowOK );
  Audio_ErrorHandler( Status2, ShowOK );
  Audio_ErrorHandler( Status3, ShowOK );
  int const Status = ( Status1==HAL_OK && Status2==HAL_OK )?  1 : -1;
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief Generate a Cosine waveform using DAC and DMA peripherals.
//! \param[in] FundamentalFrequency  Fundamental Frequency of waveform
//! \return Returns -1 in event of an Error, and 1 otherwise.
//-----------------------------------------------------------------------------
int Audio_DMA_Cosine( uint32_t const FundamentalFrequency )
{
  bool              const ShowOK             = true;
  uint32_t          const SamplingFrequency  = DAC_GetSamplingFrequency();
  uint32_t          const NumSamplesInPeriod = SamplingFrequency / FundamentalFrequency;
  if( NumSamplesInPeriod > dacBufSize ) return Audio_ErrorHandler( -1, ShowOK );
  double theta;
  for( uint32_t n=0; n<NumSamplesInPeriod  ; n++ ) 
  {
    theta = 2.0 * M_PI * (double)n / (double)NumSamplesInPeriod;
    dacBuf[n] = (uint16_t)( (double)0x0FFF * ( cos( theta ) + 1.0 ) * 0.5  );
  }
  HAL_StatusTypeDef const Status3   = DAC_Stop( );
  HAL_StatusTypeDef const Status1   = DAC_Start( );
  DMA_Config( 0 );
  HAL_StatusTypeDef const Status2   = DAC_DMA_Start( (uint32_t*)dacBuf, NumSamplesInPeriod );
  Audio_ErrorHandler( Status1, ShowOK );
  Audio_ErrorHandler( Status2, ShowOK );
  Audio_ErrorHandler( Status3, ShowOK );
  int const Status = ( Status1==HAL_OK && Status2==HAL_OK )?  1 : -1;
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief Play AudioData
//! \return Returns -1 in event of an Error, and 1 otherwise.
//-----------------------------------------------------------------------------
int Audio_AudioData(void)
{
  bool              const ShowOK  = true;
  uint32_t const NumSamples = sizeof( AudioData ) / sizeof( uint16_t );
  if( NumSamples > dacBufSize ) return Audio_ErrorHandler(-1, ShowOK);
  for( uint32_t n=0; n<NumSamples; n++ )// Copy data from Flash to RAM
    dacBuf[n] = AudioData[n];
  HAL_StatusTypeDef const Status3   = HAL_OK;  //DAC_Stop( );
  HAL_StatusTypeDef const Status1   = HAL_OK; //DAC_Start( );
  DMA_Config( 1 );
  HAL_StatusTypeDef const Status2   = DAC_DMA_Start( (uint32_t*)dacBuf, NumSamples );
  Audio_ErrorHandler( Status1, ShowOK );
  Audio_ErrorHandler( Status2, ShowOK );
  Audio_ErrorHandler( Status3, ShowOK );
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
  if( ShowOK && Status>=0 ) printf("Audio OK\r\n");
  if( Status<0 )            printf("Audio Error\r\n");
  return Status;
}

