//=============================================================================
// Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "string.h"
#include "io.h"
#include "dma.h"
#include "menu.h"
#include "AppMain.h"

extern ADC_HandleTypeDef hadc1;
extern DAC_HandleTypeDef hdac1;
extern DMA_HandleTypeDef hdma_dac1_ch1;
extern DMA_HandleTypeDef hdma_dac1_ch2;
extern ETH_HandleTypeDef heth;
extern SPI_HandleTypeDef hspi2;
extern SPI_HandleTypeDef hspi3;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
extern TIM_HandleTypeDef htim4;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim8;
extern TIM_HandleTypeDef htim13;
extern TIM_HandleTypeDef htim14;
extern TIM_HandleTypeDef htim15;
extern TIM_HandleTypeDef htim16;
extern TIM_HandleTypeDef htim17;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;

//-----------------------------------------------------------------------------
//! \brief Application main processing
//-----------------------------------------------------------------------------
int AppMain(void)
{
  DMA_Config( &hdac1, &hdma_dac1_ch1, DMA1_Stream0 );
  DMA_Config( &hdac1, &hdma_dac1_ch2, DMA1_Stream1 );
//  __HAL_RCC_TIM3_CLK_ENABLE();
//  HAL_TIM_ConfigClockSource();
//  //HAL_TIM_Base_MspInit();
//  HAL_TIM_Base_Init();
//  //HAL_TIM_IC_MspInit();
//  HAL_TIM_IC_Init();
//  HAL_TIM_IC_Start();
  Splash();
  Menu_Options( );
  uint8_t oneChar;
  uint32_t dacBuf[16] = {0x0ff, 0x1ff, 0x2ff, 0x3ff, 0x4ff, 0x5ff, 0x6ff, 0x7ff, 0x8ff, 0x9ff, 0xaff, 0xbff, 0xcff, 0xdff, 0xeff, 0xfff};
  HAL_DAC_Start( &hdac1, DAC_CHANNEL_1 );
  HAL_DAC_Start( &hdac1, DAC_CHANNEL_2 );
  HAL_DAC_Start_DMA( &hdac1, DAC_CHANNEL_1, dacBuf, 16, DAC_ALIGN_12B_R );
  HAL_DAC_Start_DMA( &hdac1, DAC_CHANNEL_2, dacBuf, 16, DAC_ALIGN_12B_R );
  HAL_TIM_Base_Start( &htim6 );

  while (1)
  {
   if( GetOneByte( &oneChar ) )
     Menu_Processing( oneChar );
  }
}
