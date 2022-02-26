//=============================================================================
// Application
// Daniel J. Greenhoe
//=============================================================================
#include "main.h"
#include "TxRx.h"

extern "C" void LED_test(void); // mixing C/C++: https://isocpp.org/wiki/faq/mixing-c-and-cpp
extern "C" void LED_Ylw_Toggle(void);
extern "C" void LED_Red_Toggle(void);
extern "C" void LED_Grn_Toggle(void);
extern "C" HAL_StatusTypeDef LED_Toggle( int n );
extern "C" HAL_StatusTypeDef LED_SetHigh( int n );
extern "C" HAL_StatusTypeDef LED_SetLow( int n );
extern "C" void LED_Sequence(uint32_t delay);
                               //   0           1           2           3           4           5           6           7           Y           R            G
GPIO_TypeDef* const LED_Bus[] = { GPIOE,      GPIOE,      GPIOE,      GPIOG,      GPIOE,      GPIOD,      GPIOD,      GPIOF,      GPIOE,      GPIOB,       GPIOB      };
const uint16_t      LED_Pin[] = { GPIO_PIN_2, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_1, GPIO_PIN_3, GPIO_PIN_1, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_1, GPIO_PIN_14, GPIO_PIN_0 };

//-----------------------------------------------------------------------------
//! \brief LED Test
//-----------------------------------------------------------------------------
void LED_test(void)
{
  LED_Red_Toggle() ; HAL_Delay(5);
  //Tx_Toggle( 5 )   ;
//LED_Toggle( 5 )  ;
  LED_Red_Toggle() ; HAL_Delay(355);
  //LED_Ylw_Toggle() ; HAL_Delay(350);
  //LED_Grn_Toggle() ; HAL_Delay(250);
}

//-----------------------------------------------------------------------------
//! \brief Toggle LED<n>
//void LED_3_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_6 ); }  // pcb rev1
//-----------------------------------------------------------------------------
HAL_StatusTypeDef LED_Toggle( int n )
{
  const int NumLEDs = sizeof(LED_Pin) / sizeof(uint16_t);
  if( n<0 || n>NumLEDs ) return HAL_ERROR;
  GPIO_TypeDef * const Bus = LED_Bus[n];
  uint16_t       const Pin = LED_Pin[n];
  HAL_GPIO_TogglePin( Bus, Pin );
  return HAL_OK;
}

//-----------------------------------------------------------------------------
//! \brief Set LED<n> High
//-----------------------------------------------------------------------------
HAL_StatusTypeDef LED_SetHigh( int n )
{
  const int NumLEDs = sizeof(LED_Pin) / sizeof(uint16_t);
  if( n<0 || n>NumLEDs ) return HAL_ERROR;
  GPIO_TypeDef * const Bus = LED_Bus[n];
  uint16_t       const Pin = LED_Pin[n];
  HAL_GPIO_WritePin( Bus, Pin, GPIO_PIN_SET );
  return HAL_OK;
}

//-----------------------------------------------------------------------------
//! \brief Set LED<n> High
//-----------------------------------------------------------------------------
HAL_StatusTypeDef LED_SetLow( int n )
{
  const int NumLEDs = sizeof(LED_Pin) / sizeof(uint16_t);
  if( n<0 || n>NumLEDs ) return HAL_ERROR;
  GPIO_TypeDef * const Bus = LED_Bus[n];
  uint16_t       const Pin = LED_Pin[n];
  HAL_GPIO_WritePin( Bus, Pin, GPIO_PIN_RESET );
  return HAL_OK;
}

//-----------------------------------------------------------------------------
// \brief Toggle Motion Board LEDs
// \params[in] delay : Delay in milliseconds after each toggle
//-----------------------------------------------------------------------------
void LED_Sequence(uint32_t delay)
{
  const int NumLEDs = sizeof(LED_Pin) / sizeof(uint16_t);
  for( int n=0; n<NumLEDs; n++ )
  {
    LED_Toggle( n );
    HAL_Delay( delay );
  }
}

//-----------------------------------------------------------------------------
//! \brief Toggle Nucleo-144 LEDs
//-----------------------------------------------------------------------------
void LED_Ylw_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1 ); }
void LED_Red_Toggle(void){ HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); }
void LED_Grn_Toggle(void){ HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0 ); }

