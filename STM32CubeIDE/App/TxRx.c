//=============================================================================
// Daniel J. Greenhoe
//=============================================================================
#include "main.h"
#include "TxRx.h"
#include <stdio.h>

static void TxRx_ErrorHandler(void);
static void Tx_SetLowHigh( uint8_t ControlByte );

GPIO_TypeDef* TxBus[] =
{
  GPIOF,
  GPIOF,
  GPIOF,
  GPIOF,
  GPIOF,
  GPIOC,
  GPIOF,
  GPIOF
};

uint16_t TxPin[] =
{
  GPIO_PIN_3 ,
  GPIO_PIN_6 ,
  GPIO_PIN_9 ,
  GPIO_PIN_7 ,
  GPIO_PIN_8 ,
  GPIO_PIN_12,
  GPIO_PIN_10,
  GPIO_PIN_0
};

GPIO_TypeDef* RxBus[] =
{
  GPIOA,
  GPIOE,
  GPIOE,
  GPIOB,
  GPIOB,
  GPIOA,
  GPIOD,
  GPIOA
};

GPIO_TypeDef* RxPin[] =
{
  GPIO_PIN_6 ,
  GPIO_PIN_9 ,
  GPIO_PIN_6 ,
  GPIO_PIN_10,
  GPIO_PIN_11,
  GPIO_PIN_0 ,
  GPIO_PIN_12,
  GPIO_PIN_6
};

//-----------------------------------------------------------------------------
//! \brief Set TX_n in accordance with bit_n of <ControlByte>
//-----------------------------------------------------------------------------
void Tx_SetLowHigh( uint8_t ControlByte )
{
  uint8_t Mask = 0x01;
  GPIO_TypeDef* Bus;
  uint16_t      Pin;
  GPIO_PinState State;
  for( int i=0; i<8; i++ )
  {
    Bus   = TxBus[i];
    Pin   = TxPin[i];
    State = ( ControlByte & Mask )? GPIO_PIN_SET : GPIO_PIN_RESET;
    HAL_GPIO_WritePin(  Bus, Pin, State );
    Mask <<= 1;
  }
}

//-----------------------------------------------------------------------------
//! \brief Toggle Tx<n> laser state
//-----------------------------------------------------------------------------
void Tx_Toggle( int n )
{
  const GPIO_TypeDef* Bus = TxBus[n];
  const uint16_t      Pin = TxPin[n];
  HAL_GPIO_TogglePin( Bus, Pin );
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser LOW
//-----------------------------------------------------------------------------
void Tx_SetLow( int n )
{
  const GPIO_TypeDef* Bus = TxBus[n];
  const uint16_t      Pin = TxPin[n];
  HAL_GPIO_WritePin(  Bus, Pin, GPIO_PIN_RESET );
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser HIGH
//-----------------------------------------------------------------------------
void Tx_SetHigh( int n )
{
  const GPIO_TypeDef* Bus = TxBus[n];
  const uint16_t      Pin = TxPin[n];
  HAL_GPIO_WritePin(  Bus, Pin, GPIO_PIN_SET );
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser LOW
//-----------------------------------------------------------------------------
void Tx_SetLowAll( void )
{
  Tx_SetLowHigh( 0x00 );
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser HIGH
//-----------------------------------------------------------------------------
void Tx_SetHighAll( void )
{
  Tx_SetLowHigh( 0xFF );
}

//-----------------------------------------------------------------------------
//! \brief Read Tx<n> laser state
//-----------------------------------------------------------------------------
int Tx_ReadState( int n )
{
  const GPIO_TypeDef* Bus      = TxBus[n];
  const uint16_t      Pin      = TxPin[n];
  const GPIO_PinState State    = HAL_GPIO_ReadPin( Bus, Pin );
  const int           RetValue = ( State==GPIO_PIN_RESET )? 0 : 1 ;
  return RetValue;
}

//-----------------------------------------------------------------------------
//! \brief Read Tx<n> laser state
//-----------------------------------------------------------------------------
int Rx_ReadState( int n )
{
  const GPIO_TypeDef* Bus      = RxBus[n];
  const uint16_t      Pin      = RxPin[n];
  const GPIO_PinState State    = HAL_GPIO_ReadPin( Bus, Pin );
  const int           RetValue = ( State==GPIO_PIN_RESET )? 0 : 1 ;
  return RetValue;
}

//-----------------------------------------------------------------------------
//! \brief Read all Tx<n> laser states
//-----------------------------------------------------------------------------
int Tx_ReadStateAll( void )
{
  int State = 0;
  for( int i=7; i>=0; i-- )
  {
    State <<= 1;
    State |= Tx_ReadState(i);
  }
  return State;
}

//-----------------------------------------------------------------------------
//! \brief Read all Rx<n> receiver states
//-----------------------------------------------------------------------------
int Rx_ReadStateAll( void )
{
  int State = 0;
  for( int i=7; i>=0; i-- )
  {
    State <<= 1;
    State |= Rx_ReadState(i);
  }
  return State;
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser LOW
//-----------------------------------------------------------------------------
static void TxRx_ErrorHandler(void)
{
  printf("TxRx Error\r\n");
}