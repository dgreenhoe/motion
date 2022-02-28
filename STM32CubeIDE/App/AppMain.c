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
#include "UserButton.h"
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
  DAC_Init();
  DMA_Init();
  DMA_Config( &hdma_dac1_ch1, DMA1_Stream0 );
  DMA_Config( &hdma_dac1_ch2, DMA1_Stream1 );
//  __HAL_RCC_TIM3_CLK_ENABLE();
//  HAL_TIM_ConfigClockSource();
//  //HAL_TIM_Base_MspInit();
//  HAL_TIM_Base_Init();
//  //HAL_TIM_IC_MspInit();
//  HAL_TIM_IC_Init();
//  HAL_TIM_IC_Start();
  Splash();
  Menu_Options( );
  uint8_t oneByte;
  uint32_t dacBuf[16] = {0x0ff, 0x1ff, 0x2ff, 0x3ff, 0x4ff, 0x5ff, 0x6ff, 0x7ff, 0x8ff, 0x9ff, 0xaff, 0xbff, 0xcff, 0xdff, 0xeff, 0xfff};
  DAC_Start();
  DAC_DMA_Start( dacBuf, sizeof(dacBuf)/sizeof(uint32_t) );
  HAL_TIM_Base_Start( &htim6 );
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
