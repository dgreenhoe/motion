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
  bool               const ShowOK = true;
  TIM_HandleTypeDef* const Handle = &htim6;
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  Handle->Instance               = TIM6;
  Handle->Init.Prescaler         = 127;
  Handle->Init.CounterMode       = TIM_COUNTERMODE_UP;
  Handle->Init.Period            = 16;
  Handle->Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_UPDATE;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_StatusTypeDef const Status1 = HAL_TIM_Base_Init( Handle );
  HAL_StatusTypeDef const Status2 = HAL_TIMEx_MasterConfigSynchronization( Handle, &sMasterConfig);
  Timer_ErrorHandler( Status1, ShowOK );
  Timer_ErrorHandler( Status2, ShowOK );
  HAL_StatusTypeDef const Status  = Status1!=HAL_OK? Status1 : Status2;
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief Start Timer 6
//! \return Return Status
//-----------------------------------------------------------------------------
HAL_StatusTypeDef Timer6_Start(void)
{
  bool               const ShowOK = true;
  TIM_HandleTypeDef* const Handle = &htim6;
  HAL_StatusTypeDef  const Status = HAL_TIM_Base_Start( Handle );
  return Timer_ErrorHandler( Status, ShowOK );
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