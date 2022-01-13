//=============================================================================
// Application
// Daniel J. Greenhoe
//=============================================================================
extern "C" void LED_test(void); // mixing C/C++: https://isocpp.org/wiki/faq/mixing-c-and-cpp
#include "main.h"
#include "LEDs.h"
void Tx_Toggle(uint32_t delay);
void LED_Toggle(uint32_t delay);

void LED_test(void)
{
  LED_Red_Toggle() ; HAL_Delay(5);
  Tx_Toggle( 5 )   ;
//LED_Toggle( 5 )  ;
  LED_Red_Toggle() ; HAL_Delay(355);
  //LED_Ylw_Toggle() ; HAL_Delay(350);
  //LED_Grn_Toggle() ; HAL_Delay(250);
}

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
// \brief Toggle Motion Board lasers
// \params[in] delay : Delay in milliseconds after each toggle
//-----------------------------------------------------------------------------
void Tx_Toggle(uint32_t delay)
{
  Tx_0_Toggle(); HAL_Delay( delay );
  Tx_1_Toggle(); HAL_Delay( delay );
  Tx_2_Toggle(); HAL_Delay( delay );
  Tx_3_Toggle(); HAL_Delay( delay );
  Tx_4_Toggle(); HAL_Delay( delay );
  Tx_5_Toggle(); HAL_Delay( delay );
  Tx_6_Toggle(); HAL_Delay( delay );
  Tx_7_Toggle(); HAL_Delay( delay );
}


