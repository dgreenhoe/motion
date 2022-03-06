//=============================================================================
// Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "string.h"
#include "io.h"
#include "dac.h"
#include "dma.h"
#include "menu.h"
#include "LEDs.h"
#include "TxRx.h"
#include "Timers.h"
#include "UserButton.h"
#include "Audio.h"
#include "AppMain.h"

extern ADC_HandleTypeDef  hadc1;
extern DAC_HandleTypeDef  hdac1;
extern DMA_HandleTypeDef  hdma_dac1_ch1;
extern DMA_HandleTypeDef  hdma_dac1_ch2;
extern ETH_HandleTypeDef  heth;
extern SPI_HandleTypeDef  hspi2;
extern SPI_HandleTypeDef  hspi3;
extern TIM_HandleTypeDef  htim1;
extern TIM_HandleTypeDef  htim2;
extern TIM_HandleTypeDef  htim3;
extern TIM_HandleTypeDef  htim4;
extern TIM_HandleTypeDef  htim5;
extern TIM_HandleTypeDef  htim6;
extern TIM_HandleTypeDef  htim8;
extern TIM_HandleTypeDef  htim13;
extern TIM_HandleTypeDef  htim14;
extern TIM_HandleTypeDef  htim15;
extern TIM_HandleTypeDef  htim16;
extern TIM_HandleTypeDef  htim17;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

//-----------------------------------------------------------------------------
//! \brief Application main processing
//-----------------------------------------------------------------------------
int AppMain(void)
{
  int DetectOn=0, RxState=0;
  uint8_t oneByte;
  uint32_t const FundamentalFrequency = 440;

  Timer6_Init();
  DAC_Init();
  DMA_Init();
  DMA_Config( &hdma_dac1_ch1, DMA1_Stream0 );
  DMA_Config( &hdma_dac1_ch2, DMA1_Stream1 );
  Splash();
  Menu_Options( );
  Timer6_Start( );
//Audio_DMA_SawTooth( FundamentalFrequency );
//Audio_DMA_Triangle( FundamentalFrequency );
//Audio_DMA_Square(   FundamentalFrequency );
  Audio_DMA_Cosine(   FundamentalFrequency );

  TxRx_TestAll( );

  while (1)
  {
    if( GetOneByte( &oneByte ) )
      Menu_Processing( oneByte );
    if( Button_Pressed()==1 )
    {
      if( DetectOn==0 )
      {
        DetectOn = 1;
        Tx_SetHighAll();
        LED_Grn_On();
      }
      else
      {
        DetectOn = 0;
        Tx_SetLowAll();
        LED_Grn_Off();
      }
    }
    if( DetectOn==1 )
    {
      RxState = Rx_ReadStateAll();
      if( RxState != 0xFF )
      {
        LED_Red_On();
        HAL_Delay(1000);
        LED_Red_Off();
      }
    }
  }
  return -1;
}

//-----------------------------------------------------------------------------
//! \brief Display HAL Status
//! \param[in] Status HAL Status code
//! \param[in] ShowOK If Status=HAL_OK, hide any messages.
//! \return Return Status
//-----------------------------------------------------------------------------
HAL_StatusTypeDef Display_HAL_Status( HAL_StatusTypeDef const Status, bool const ShowOK )
{
  if( ShowOK || Status!=HAL_OK )
  {
    printf("HAL Status = %d ", Status);
    switch( Status )
    {
      case HAL_OK      : printf("(OK)"      ); break;
      case HAL_ERROR   : printf("(Error)"   ); break;
      case HAL_BUSY    : printf("(Busy)"    ); break;
      case HAL_TIMEOUT : printf("(TimeOut)" ); break;
      default          : printf("(Unknown)" ); break;
    }
    printf("\r\n");
  }
  return Status;
}