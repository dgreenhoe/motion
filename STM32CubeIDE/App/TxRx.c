//=============================================================================
// Daniel J. Greenhoe
//=============================================================================
#include <stdio.h>
#include <stdbool.h>
#include "main.h"
#include "LEDs.h"
#include "TxRx.h"

static void TxRx_ErrorHandler(void);
static void Tx_SetLowHigh( uint8_t ControlByte );
uint8_t TxRxError = 0x00;
                             //   0           1           2           3            4            5            6            7
GPIO_TypeDef* const TxBus[] = { GPIOF,      GPIOF,      GPIOF,      GPIOF,       GPIOF,       GPIOC,       GPIOF,       GPIOF      };
uint16_t      const TxPin[] = { GPIO_PIN_3, GPIO_PIN_6, GPIO_PIN_9, GPIO_PIN_7,  GPIO_PIN_8,  GPIO_PIN_12, GPIO_PIN_10, GPIO_PIN_0 };
GPIO_TypeDef* const RxBus[] = { GPIOA,      GPIOE,      GPIOE,      GPIOB,       GPIOB,       GPIOA,       GPIOD,       GPIOC      };
uint16_t      const RxPin[] = { GPIO_PIN_6, GPIO_PIN_9, GPIO_PIN_6, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_0,  GPIO_PIN_12, GPIO_PIN_8 };

//-----------------------------------------------------------------------------
//! \brief Set TX_n in accordance with bit_n of <ControlByte>
//! \param[in] ControlByte : Bit<n>=0 sets Tx<n> to Low, and 1 to High
//-----------------------------------------------------------------------------
void Tx_SetLowHigh( uint8_t ControlByte )
{
  int const NumTx = TxRx_GetNumChannels();
  uint8_t Mask = 0x01;
  bool Level;
  for( int n=0; n<NumTx; n++ )
  {
    Level = (bool)( ControlByte & Mask );
    Tx_SetLevel( n, Level );
    Mask <<= 1;
  }
}

//-----------------------------------------------------------------------------
//! \brief Toggle Tx<n> state
//! \param[in] n : Tx state index
//-----------------------------------------------------------------------------
void Tx_Toggle( int const n )
{
  int const CurrentPinState = Rx_ReadState( n );
  switch( CurrentPinState )
  {
    case 0  : Tx_SetLevel( n, true  ); break;
    case 1  : Tx_SetLevel( n, false ); break;
    default :                          break;
  }
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser HIGH
//! \param[in] n : Tx state index
//-----------------------------------------------------------------------------
void Tx_SetLevel( int const n, bool const Level )
{
  GPIO_PinState const PinState = Level ? GPIO_PIN_SET : GPIO_PIN_RESET;
  int           const NumTx    = TxRx_GetNumChannels();
  if( n<0 || n>=NumTx ) {TxRx_ErrorHandler(); return; }
  GPIO_TypeDef* const Bus   = TxBus[n];
  uint16_t      const Pin   = TxPin[n];
  HAL_GPIO_WritePin(  Bus, Pin, PinState );
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser LOW
//! \param[in] n : Tx state index
//-----------------------------------------------------------------------------
void Tx_SetLow( int const n )
{
  Tx_SetLevel( n, false );
}

//-----------------------------------------------------------------------------
//! \brief Set Tx<n> laser to <Level>
//! \param[in] n : Tx state index
//-----------------------------------------------------------------------------
void Tx_SetHigh( int const n )
{
  Tx_SetLevel( n, true );
}

//-----------------------------------------------------------------------------
//! \brief Set all Tx<n> to LOW
//-----------------------------------------------------------------------------
void Tx_SetLowAll( void )
{
  Tx_SetLowHigh( 0x00 );
}

//-----------------------------------------------------------------------------
//! \brief Set all Tx<n> to HIGH
//-----------------------------------------------------------------------------
void Tx_SetHighAll( void )
{
  Tx_SetLowHigh( 0xFF );
}

//-----------------------------------------------------------------------------
//! \brief Set all Tx<n> to HIGH
//-----------------------------------------------------------------------------
void Tx_ToggleAll( void )
{
  const int CurrentState = Tx_ReadStateAll();
  const int NewState     = (~CurrentState) & (int)0x00ff;
  Tx_SetLowHigh( NewState );
}

//-----------------------------------------------------------------------------
//! \brief Get number of TxRx channels
//! \return -1=Error, otherwise number of channels
//-----------------------------------------------------------------------------
int TxRx_GetNumChannels( void )
{
  int const NumTx = sizeof(TxPin) / sizeof(uint16_t);
  return NumTx;
}

//-----------------------------------------------------------------------------
//! \brief Read Tx<n> state
//! \param[in] n : Tx state index
//! \return 0=Low-state  1=High-state  -1=Error
//-----------------------------------------------------------------------------
int Tx_ReadState( int const n )
{
  int           const NumTx    = sizeof(TxPin) / sizeof(uint16_t);
  if( n<0 || n>=NumTx ) {TxRx_ErrorHandler(); return -1; }
  GPIO_TypeDef* const Bus      = TxBus[n];
  uint16_t      const Pin      = TxPin[n];
  GPIO_PinState const State    = HAL_GPIO_ReadPin( Bus, Pin );
  int           const RetValue = ( State==GPIO_PIN_RESET )? 0 : 1 ;
  return RetValue;
}

//-----------------------------------------------------------------------------
//! \brief Read Rx<n> state
//! \param[in] n : Tx state index
//! \return 0=Low-state  1=High-state  -1=Error
//-----------------------------------------------------------------------------
int Rx_ReadState( int const n )
{
  int           const NumRx    = TxRx_GetNumChannels();
  if( n<0 || n>=NumRx ) {TxRx_ErrorHandler(); return -1; }
  GPIO_TypeDef* const Bus      = RxBus[n];
  uint16_t      const Pin      = RxPin[n];
  GPIO_PinState const State    = HAL_GPIO_ReadPin( Bus, Pin );
  int           const RetValue = ( State==GPIO_PIN_RESET )? 0 : 1 ;
  return RetValue;
}

//-----------------------------------------------------------------------------
//! \brief Read all Tx<n> states
//! \return Bit<n>=0 indicates Tx<n>=Low, 1 indicates High
//-----------------------------------------------------------------------------
int Tx_ReadStateAll( void )
{
  int           const NumRx = TxRx_GetNumChannels();
  int State = 0;
  for( int n=NumRx-1; n>=0; n-- )
  {
    State <<= 1;
    State |= Tx_ReadState(n);
  }
  return State;
}

//-----------------------------------------------------------------------------
//! \brief Read all Rx<n> receiver states
//-----------------------------------------------------------------------------
int Rx_ReadStateAll( void )
{
  int State = 0;
  int const NumRx = TxRx_GetNumChannels();
  for( int n=NumRx-1; n>=0; n-- )
  {
    State <<= 1;
    State |= Rx_ReadState(n);
  }
  return State;
}

//-----------------------------------------------------------------------------
//! \brief Test all transmitter-receiver channels
//-----------------------------------------------------------------------------
int TxRx_TestAll( void )
{
  int const NumTx = TxRx_GetNumChannels();
  uint32_t const Duration = 10;
  TxRxError = 0x00; // clear error flags
  for( int n=0; n<NumTx; n++ ) TxRx_Test( n, Duration );
  Tx_ToggleAll();
  for( int n=0; n<NumTx; n++ ) TxRx_Test( n, Duration );
  Tx_ToggleAll();
  return 0;
}

//-----------------------------------------------------------------------------
//! \brief Test transmitter-receiver channel <n>
//! \param[in] n : Channel index
//! \param[in] Duration: Duration in milliseconds between test segments
//-----------------------------------------------------------------------------
int TxRx_Test( int const n, uint32_t const Duration )
{
  int     const TxState   = Tx_ReadState( n ); // Read initial Tx<n> state
  uint8_t const BitMarker = 0x01<<n;
  int Status;
  int RxState;
  LED_Off( n );
  Tx_SetHigh( n );
  HAL_Delay( Duration );
  RxState = Rx_ReadState(n);
  printf("TxRx %d Test: Tx=1 Rx=%d ", n, RxState );
  if( RxState == 1 ) printf("OK!  ");
  else
  {
    printf("FAIL ");
    TxRxError |= BitMarker; // set error flag
  }
  Tx_SetLow( n );
  HAL_Delay( Duration );
  RxState = Rx_ReadState(n);
  printf("Tx=0 Rx=%d ", RxState );
  if( RxState == 0 ) printf("OK!  ");
  else
  {
    printf("FAIL ");
    TxRxError |= BitMarker; // set error flag
  }
  printf("\r\n");
  if( TxRxError & BitMarker )
  {
    LED_On( n );
    Status = -1;
  }
  else
  {
  LED_Pulsate( n );
  Status = 0;
  }
  Tx_SetLevel( n, TxState ); // Restore initial Tx<n> state
  return Status;
}

//-----------------------------------------------------------------------------
//! \brief TxRx Error Handler
//-----------------------------------------------------------------------------
static void TxRx_ErrorHandler(void)
{
  printf("TxRx Error\r\n");
}

