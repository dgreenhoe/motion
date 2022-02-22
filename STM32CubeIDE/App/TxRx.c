//=============================================================================
// Daniel J. Greenhoe
//=============================================================================
#include "main.h"
#include "TxRx.h"
#include <stdio.h>

static void TxRx_ErrorHandler(void);

//-----------------------------------------------------------------------------
//! \brief Toggle Tx<n> laser state
//-----------------------------------------------------------------------------
void Tx_Toggle( int n )
{
  switch( n )
  {
    case 0 : HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_3  ); break;
    case 1 : HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_6  ); break;
    case 2 : HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_9  ); break;
    case 3 : HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_7  ); break;
    case 4 : HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_8  ); break;
    case 5 : HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_12 ); break;
    case 6 : HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_10 ); break;
    case 7 : HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_0  ); break;
    default: TxRx_ErrorHandler();
  }
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser LOW
//-----------------------------------------------------------------------------
void Tx_SetLow( int n )
{
  switch( n )
  {
    case 0 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3 , GPIO_PIN_RESET ); break;
    case 1 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6 , GPIO_PIN_RESET ); break;
    case 2 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9 , GPIO_PIN_RESET ); break;
    case 3 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7 , GPIO_PIN_RESET ); break;
    case 4 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8 , GPIO_PIN_RESET ); break;
    case 5 : HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_RESET ); break;
    case 6 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_RESET ); break;
    case 7 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0 , GPIO_PIN_RESET ); break;
    default: TxRx_ErrorHandler();
  }
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser HIGH
//-----------------------------------------------------------------------------
void Tx_SetHigh( int n )
{
  switch( n )
  {
    case 0 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_3 , GPIO_PIN_SET ); break;
    case 1 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_6 , GPIO_PIN_SET ); break;
    case 2 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_9 , GPIO_PIN_SET ); break;
    case 3 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_7 , GPIO_PIN_SET ); break;
    case 4 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_8 , GPIO_PIN_SET ); break;
    case 5 : HAL_GPIO_WritePin(GPIOC, GPIO_PIN_12, GPIO_PIN_SET ); break;
    case 6 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_10, GPIO_PIN_SET ); break;
    case 7 : HAL_GPIO_WritePin(GPIOF, GPIO_PIN_0 , GPIO_PIN_SET ); break;
    default: TxRx_ErrorHandler();
  }
}

//-----------------------------------------------------------------------------
//! \brief Read Tx<n> laser state
//-----------------------------------------------------------------------------
int Tx_ReadState( int n )
{
  GPIO_PinState PinState = GPIO_PIN_SET;
  switch( n )
  {
    case 0 : PinState = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_3  ); break;
    case 1 : PinState = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_6  ); break;
    case 2 : PinState = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_9  ); break;
    case 3 : PinState = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_7  ); break;
    case 4 : PinState = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_8  ); break;
    case 5 : PinState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_12 ); break;
    case 6 : PinState = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_10 ); break;
    case 7 : PinState = HAL_GPIO_ReadPin(GPIOF, GPIO_PIN_0  ); break;
    default: TxRx_ErrorHandler();
  }
  const int  RetValue = ( PinState==GPIO_PIN_RESET )? 0 : 1 ;
  return     RetValue;
}

//-----------------------------------------------------------------------------
//! \brief Read Tx<n> laser state
//-----------------------------------------------------------------------------
int Rx_ReadState( int n )
{
  GPIO_PinState PinState = GPIO_PIN_SET;
  switch( n )
  {
    case 0 : PinState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_6  ); break;
    case 1 : PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_9  ); break;
    case 2 : PinState = HAL_GPIO_ReadPin(GPIOE, GPIO_PIN_6  ); break;
    case 3 : PinState = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10 ); break;
    case 4 : PinState = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11 ); break;
    case 5 : PinState = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0  ); break;
    case 6 : PinState = HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_12 ); break;
    case 7 : PinState = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6  ); break;
    default: TxRx_ErrorHandler();
  }
  const int  RetValue = ( PinState==GPIO_PIN_RESET )? 0 : 1 ;
  return     RetValue;
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser LOW
//-----------------------------------------------------------------------------
static void TxRx_ErrorHandler(void)
{
  printf("TxRx Error\r\n");
}