//=============================================================================
// Timers Configuration
// Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "AppMain.h"
#include "Timers.h"
static HAL_StatusTypeDef Timer_ErrorHandler( HAL_StatusTypeDef const Status, bool const ShowOK );

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

//-----------------------------------------------------------------------------
//! \brief Configure Memory-to-DAC DMA stream
//! \details 96MHz / (127+1) / (16+1) = 44.11765 kHz
//! \param[in] hdac Pointer to DAC handle
//! \param[in] hdma Pointer to DMA handle
//-----------------------------------------------------------------------------
HAL_StatusTypeDef Timer6_Init(void)
{
  bool const ShowOK = true;
  HAL_StatusTypeDef Status = HAL_OK;
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  htim6.Instance = TIM6;
  htim6.Init.Prescaler         = 127;
  htim6.Init.CounterMode       = TIM_COUNTERMODE_UP;
  htim6.Init.Period            = 16;
  htim6.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim6) != HAL_OK)
  {
    Timer_ErrorHandler( Status, ShowOK );
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim6, &sMasterConfig) != HAL_OK)
  {
    Timer_ErrorHandler( Status, ShowOK );
  }
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief Configure Memory-to-DAC DMA stream
//! \details 
//! \param[in] Status HAL Status code
//! \param[in] ShowOK If Status=HAL_OK, hide any messages.
//! \return Return Status
//-----------------------------------------------------------------------------
static HAL_StatusTypeDef Timer_ErrorHandler( HAL_StatusTypeDef const Status, bool const ShowOK )
{
  if( !ShowOK || Status!=HAL_OK )
  {
    printf("Timer " );
    Display_HAL_Status( Status, ShowOK );
  }
  return Status;
}