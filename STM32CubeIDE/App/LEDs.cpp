//=============================================================================
// Application
// Daniel J. Greenhoe
//=============================================================================
#include<stdio.h>
#include "main.h"
//#include "TxRx.h"

static void LED_ErrorHandler(void);

extern "C" void LED_test(void); // mixing C/C++: https://isocpp.org/wiki/faq/mixing-c-and-cpp

extern "C" void LED_Ylw_Toggle(void);
extern "C" void LED_Red_Toggle(void);
extern "C" void LED_Grn_Toggle(void);

extern "C" void LED_Ylw_On(void);
extern "C" void LED_Red_On(void);
extern "C" void LED_Grn_On(void);

extern "C" void LED_Ylw_Off(void);
extern "C" void LED_Red_Off(void);
extern "C" void LED_Grn_Off(void);

extern "C" void LED_Toggle( int n );
extern "C" void LED_On( int n );
extern "C" void LED_Off( int n );
extern "C" void LED_Sequence(uint32_t delay);

typedef enum { LED0, LED1, LED2, LED3, LED4, LED5, LED6, LED7, LEDY, LEDR, LEDG } LED_t;
                               //   0           1           2           3           4           5           6           7           Y           R            G
GPIO_TypeDef* const LED_Bus[] = { GPIOE,      GPIOE,      GPIOE,      GPIOG,      GPIOE,      GPIOD,      GPIOD,      GPIOF,      GPIOE,      GPIOB,       GPIOB      };
uint16_t      const LED_Pin[] = { GPIO_PIN_2, GPIO_PIN_4, GPIO_PIN_5, GPIO_PIN_1, GPIO_PIN_3, GPIO_PIN_1, GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_1, GPIO_PIN_14, GPIO_PIN_0 };

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
void LED_Toggle( int n )
{
  const int NumLEDs = sizeof(LED_Pin) / sizeof(uint16_t);
  if( n<0 || n>=NumLEDs ) return LED_ErrorHandler();
  GPIO_TypeDef * const Bus = LED_Bus[n];
  uint16_t       const Pin = LED_Pin[n];
  HAL_GPIO_TogglePin( Bus, Pin );
}

//-----------------------------------------------------------------------------
//! \brief Set LED<n> High
//-----------------------------------------------------------------------------
void LED_On( int n )
{
  const int NumLEDs = sizeof(LED_Pin) / sizeof(uint16_t);
  if( n<0 || n>=NumLEDs ) return LED_ErrorHandler();
  GPIO_TypeDef * const Bus = LED_Bus[n];
  uint16_t       const Pin = LED_Pin[n];
  HAL_GPIO_WritePin( Bus, Pin, GPIO_PIN_SET );
}

//-----------------------------------------------------------------------------
//! \brief Set LED<n> High
//-----------------------------------------------------------------------------
void LED_Off( int n )
{
  const int NumLEDs = sizeof(LED_Pin) / sizeof(uint16_t);
  if( n<0 || n>=NumLEDs ) return LED_ErrorHandler();
  GPIO_TypeDef * const Bus = LED_Bus[n];
  uint16_t       const Pin = LED_Pin[n];
  HAL_GPIO_WritePin( Bus, Pin, GPIO_PIN_RESET );
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
void LED_Ylw_Toggle(void){ HAL_GPIO_TogglePin( LED_Bus[LEDY], LED_Pin[LEDY] ); }
void LED_Red_Toggle(void){ HAL_GPIO_TogglePin( LED_Bus[LEDR], LED_Pin[LEDR] ); }
void LED_Grn_Toggle(void){ HAL_GPIO_TogglePin( LED_Bus[LEDG], LED_Pin[LEDG] ); }

//-----------------------------------------------------------------------------
//! \brief Set Nucleo-144 LEDs to ON
//-----------------------------------------------------------------------------
void LED_Ylw_On(void){ HAL_GPIO_WritePin( LED_Bus[LEDY], LED_Pin[LEDY], GPIO_PIN_SET ); }
void LED_Red_On(void){ HAL_GPIO_WritePin( LED_Bus[LEDR], LED_Pin[LEDR], GPIO_PIN_SET ); }
void LED_Grn_On(void){ HAL_GPIO_WritePin( LED_Bus[LEDG], LED_Pin[LEDG], GPIO_PIN_SET ); }

//-----------------------------------------------------------------------------
//! \brief Set Nucleo-144 LEDs to OFF
//-----------------------------------------------------------------------------
void LED_Ylw_Off(void){ HAL_GPIO_WritePin( LED_Bus[LEDY], LED_Pin[LEDY], GPIO_PIN_RESET ); }
void LED_Red_Off(void){ HAL_GPIO_WritePin( LED_Bus[LEDR], LED_Pin[LEDR], GPIO_PIN_RESET ); }
void LED_Grn_Off(void){ HAL_GPIO_WritePin( LED_Bus[LEDG], LED_Pin[LEDG], GPIO_PIN_RESET ); }

//-----------------------------------------------------------------------------
//! \brief LED Error Handler
//-----------------------------------------------------------------------------
static void LED_ErrorHandler(void)
{
  printf("LED Error\r\n");
}