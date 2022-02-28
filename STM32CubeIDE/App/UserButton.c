//=============================================================================
// Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "LEDs.h"
#include "TxRx.h"
#include "UserButton.h"

//-----------------------------------------------------------------------------
//! \brief Read Button Level
//! \return 0 on event Level=Low, 1 on event Level=High, -1 on Error event
//-----------------------------------------------------------------------------
int Button_ReadLevel( void )
{
  GPIO_TypeDef* const Bus   = GPIOC;
  uint16_t      const Pin   = GPIO_PIN_13;
  GPIO_PinState const State = HAL_GPIO_ReadPin( Bus, Pin );
  int ReturnValue;
  switch( State )
  {
    case GPIO_PIN_RESET : ReturnValue =  0; break;
    case GPIO_PIN_SET   : ReturnValue =  1; break;
    default             : ReturnValue = -1; break;
  }
  return ReturnValue;
}

//-----------------------------------------------------------------------------
//! \brief Button Pressed?
//! \return -1 on Error event; 1 on event transition from Low to High; 0 otherwise
//-----------------------------------------------------------------------------
int Button_Pressed( void )
{
  static int PreviousLevel = 0;
  int const CurrentLevel   = Button_ReadLevel();
  int ReturnValue          = -1;
  if( (PreviousLevel==0) && (CurrentLevel==0) ) ReturnValue=0; // Low and holding
  if( (PreviousLevel==0) && (CurrentLevel==1) ) ReturnValue=1; // Transition Low to High
  if( (PreviousLevel==1) && (CurrentLevel==0) ) ReturnValue=0; // Transition High to Low
  if( (PreviousLevel==1) && (CurrentLevel==1) ) ReturnValue=0; // High and holding
  PreviousLevel = CurrentLevel;
  return ReturnValue;
}