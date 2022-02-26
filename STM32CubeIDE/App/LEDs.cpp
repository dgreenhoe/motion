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
extern "C" void LED_0_Toggle(void);
extern "C" void LED_1_Toggle(void);
extern "C" void LED_2_Toggle(void);
extern "C" void LED_3_Toggle(void);
extern "C" void LED_4_Toggle(void);
extern "C" void LED_5_Toggle(void);
extern "C" void LED_6_Toggle(void);
extern "C" void LED_7_Toggle(void);

void Tx_Toggle(uint32_t delay);
void LED_Toggle(uint32_t delay);

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
//-----------------------------------------------------------------------------
void LED_0_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_2 ); }
void LED_1_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_4 ); }
void LED_2_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_5 ); }
//void LED_3_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_6 ); }  // pcb rev1
void LED_3_Toggle(void){ HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_1 ); }
void LED_4_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_3 ); }
void LED_5_Toggle(void){ HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_1 ); }
void LED_6_Toggle(void){ HAL_GPIO_TogglePin(GPIOD, GPIO_PIN_0 ); }
void LED_7_Toggle(void){ HAL_GPIO_TogglePin(GPIOF, GPIO_PIN_1 ); }

//-----------------------------------------------------------------------------
// \brief Toggle Motion Board LEDs
// \params[in] delay : Delay in milliseconds after each toggle
//-----------------------------------------------------------------------------
void LED_Toggle(uint32_t delay)
{
  LED_0_Toggle(); HAL_Delay( delay );
  LED_1_Toggle(); HAL_Delay( delay );
  LED_2_Toggle(); HAL_Delay( delay );
  LED_3_Toggle(); HAL_Delay( delay );
  LED_4_Toggle(); HAL_Delay( delay );
  LED_5_Toggle(); HAL_Delay( delay );
  LED_6_Toggle(); HAL_Delay( delay );
  LED_7_Toggle(); HAL_Delay( delay );
}

//-----------------------------------------------------------------------------
//! \brief Toggle Nucleo-144 LEDs
//-----------------------------------------------------------------------------
void LED_Ylw_Toggle(void){ HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1 ); }
void LED_Red_Toggle(void){ HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_14); }
void LED_Grn_Toggle(void){ HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0 ); } 

