//=============================================================================
// Daniel J. Greenhoe
//=============================================================================
#include "main.h"
#include "LEDs.h"
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
  GPIOC
};

uint16_t RxPin[] =
{
  GPIO_PIN_6 ,
  GPIO_PIN_9 ,
  GPIO_PIN_6 ,
  GPIO_PIN_10,
  GPIO_PIN_11,
  GPIO_PIN_0 ,
  GPIO_PIN_12,
  GPIO_PIN_8
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
  int           const NumTx = sizeof(TxPin) / sizeof(uint16_t);
  if( n<0 || n>=NumTx ) {TxRx_ErrorHandler(); return; }
  GPIO_TypeDef* const Bus   = TxBus[n];
  uint16_t      const Pin   = TxPin[n];
  HAL_GPIO_TogglePin( Bus, Pin );
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser LOW
//-----------------------------------------------------------------------------
void Tx_SetLow( int n )
{
  int           const NumTx = sizeof(TxPin) / sizeof(uint16_t);
  if( n<0 || n>=NumTx ) {TxRx_ErrorHandler(); return; }
  GPIO_TypeDef* const Bus   = TxBus[n];
  uint16_t      const Pin   = TxPin[n];
  HAL_GPIO_WritePin(  Bus, Pin, GPIO_PIN_RESET );
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser HIGH
//-----------------------------------------------------------------------------
void Tx_SetHigh( int n )
{
  int           const NumTx = sizeof(TxPin) / sizeof(uint16_t);
  if( n<0 || n>=NumTx ) {TxRx_ErrorHandler(); return; }
  GPIO_TypeDef* const Bus   = TxBus[n];
  uint16_t      const Pin   = TxPin[n];
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
  GPIO_TypeDef* const Bus      = TxBus[n];
  uint16_t      const Pin      = TxPin[n];
  GPIO_PinState const State    = HAL_GPIO_ReadPin( Bus, Pin );
  int           const RetValue = ( State==GPIO_PIN_RESET )? 0 : 1 ;
  return RetValue;
}

//-----------------------------------------------------------------------------
////! \brief Read Tx<n> laser state
//-----------------------------------------------------------------------------
int Rx_ReadState( int n )
{
  int           const NumTx    = sizeof(TxPin) / sizeof(uint16_t);
  if( n<0 || n>=NumTx ) {TxRx_ErrorHandler(); return -1; }
  GPIO_TypeDef* const Bus      = RxBus[n];
  uint16_t      const Pin      = RxPin[n];
  GPIO_PinState const State    = HAL_GPIO_ReadPin( Bus, Pin );
  int           const RetValue = ( State==GPIO_PIN_RESET )? 0 : 1 ;
  return RetValue;
}

//-----------------------------------------------------------------------------
//! \brief Read all Tx<n> laser states
//-----------------------------------------------------------------------------
int Tx_ReadStateAll( void )
{
  int           const NumTx = sizeof(TxPin) / sizeof(uint16_t);
  int State = 0;
  for( int i=NumTx-1; i>=0; i-- )
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
  int const NumTx = sizeof(TxPin) / sizeof(uint16_t);
  for( int i=NumTx-1; i>=0; i-- )
  {
    State <<= 1;
    State |= Rx_ReadState(i);
  }
  return State;
}

//-----------------------------------------------------------------------------
//! \brief Test laser transmitter-receiver channels
//-----------------------------------------------------------------------------
int TxRx_Test( int n )
{
  int Status = 0;
  int RxState;
  uint32_t const milliseconds = 500;
  LED_Off( n );
  Tx_SetHigh( n );
  HAL_Delay( milliseconds );
  RxState = Rx_ReadState(n);
  if( RxState != 1 )
  {
    Status = -1;
    printf("Tx%d_SetHigh but Rx%d_State=%d\r\n", n, n, RxState);
    TxRx_ErrorHandler();
    LED_On( n );
    return -1;
  }
  Tx_SetLow( n );
  HAL_Delay( milliseconds );
  RxState = Rx_ReadState(n);
  if( RxState != 0 ) 
  {
    Status = -1;
    printf("Tx%d_SetLow but Rx%d_State=%d\r\n", n, n, RxState);
    TxRx_ErrorHandler();
    LED_On( n );
    return -1;
  }
  LED_Pulsate( n );
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief TxRx Error Handler
//-----------------------------------------------------------------------------
static void TxRx_ErrorHandler(void)
{
  printf("TxRx Error\r\n");
}

